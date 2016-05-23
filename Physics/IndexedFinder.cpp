#include "IndexedFinder.h"
#include "IndexedParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

void IndexedFinder::add(const std::vector<IndexedParticle>& particles)
{
	iparticles = particles;
	for (auto& particle : iparticles) {
		particle.setGridID(effectLength);
	}
	std::sort(iparticles.begin(), iparticles.end());
}


void IndexedFinder::add(const std::vector<SPHParticle*>& particles)
{
	for (const auto& particle : particles) {
		iparticles.push_back(IndexedParticle(particle));
	}

	for (auto& particle : iparticles) {
		particle.setGridID(effectLength);
	}

	std::sort(iparticles.begin(), iparticles.end());
}

void IndexedFinder::createPairs(std::vector<SPHParticle*> particles)
{
	if (particles.empty()) {
		return;
	}

	// optimization for quad core.
	const int threads = 8;

	std::vector<std::vector<SPHParticlePair>> eachPairs(threads);

	std::vector<std::vector<IndexedParticle>::const_iterator> iters;
	for (int i = 0; i < threads; ++i) {
		iters.push_back(iparticles.begin() + i * iparticles.size() / threads);
	}
	iters.push_back(iparticles.end());

#pragma omp parallel for
	for (int i = 0; i < threads; ++i) {
		eachPairs[i] = search1(iparticles, iters[i], iters[i + 1], effectLength * effectLength);

	}

	for (size_t i = 0; i < eachPairs.size(); ++i) {
		pairs.insert(pairs.end(), eachPairs[i].begin(), eachPairs[i].end());
	}

#pragma omp parallel for
	for (int i = 0; i < threads; ++i) {
		eachPairs[i] = search2(iparticles, iters[i], iters[i + 1], effectLength * effectLength);
	}

	for (size_t i = 0; i < eachPairs.size(); ++i) {
		pairs.insert(pairs.end(), eachPairs[i].begin(), eachPairs[i].end());
	}
}

std::vector<SPHParticlePair> IndexedFinder::search1(const std::vector<IndexedParticle>& particles, std::vector<IndexedParticle>::const_iterator startIter, std::vector<IndexedParticle>::const_iterator endIter, const float effectLengthSquared)
{
	std::vector<SPHParticlePair> pairs;
	for (auto xIter = startIter; xIter != endIter; ++xIter) {
		const auto gridID = xIter->getGridID();
		const auto& centerX = xIter->getPosition();
		auto yIter = xIter;
		++yIter;// ignore itself.
		while (yIter != particles.end() && (yIter->getGridID() <= gridID + 1)) {
			const auto& centerY = yIter->getPosition();
			if (centerX.getDistanceSquared(centerY) < effectLengthSquared) {
				/*
				if (xIter->getParticle()->isBoundary() && yIter->getParticle()->isBoundary()) {
					++yIter;
					continue;
				}
				*/
				pairs.push_back(SPHParticlePair(xIter->getParticle(), yIter->getParticle()));
				//pairs.push_back(SPHParticlePair((*yIter), (*xIter)));
			}
			++yIter;
		}
	}
	return pairs;
}

std::vector<SPHParticlePair> IndexedFinder::search2(const std::vector<IndexedParticle>& particles, std::vector<IndexedParticle>::const_iterator startIter, std::vector<IndexedParticle>::const_iterator endIter, const float effectLengthSquared)
{
	std::vector<SPHParticlePair> pairs;

	std::vector<std::vector<IndexedParticle>::const_iterator> yIter(4, startIter);
	std::vector<int> offsetIds;
	offsetIds.push_back(1023);
	offsetIds.push_back(1047551);
	offsetIds.push_back(1048575);
	offsetIds.push_back(1049599);

	for (std::vector<IndexedParticle>::const_iterator xIter = startIter; xIter != endIter; ++xIter) {
		for (size_t i = 0; i < 4; ++i) {
			const auto baseID = xIter->getGridID() + offsetIds[i];
			while (yIter[i] != particles.end() && (yIter[i]->getGridID() < baseID)) {
				++yIter[i];
			}

			const auto& centerX = xIter->getPosition();
			auto zIter = yIter[i];
			while (zIter != particles.end() && zIter->getGridID() <= baseID + 2) {
				const auto& centerZ = zIter->getPosition();
				if (centerX.getDistanceSquared(centerZ) < effectLengthSquared) {
					/*
					if (xIter->getParticle()->isBoundary() && zIter->getParticle()->isBoundary()) {
						++zIter;
						continue;
					}
					*/
					pairs.push_back(SPHParticlePair(xIter->getParticle(), zIter->getParticle()));
					//pairs.push_back(SPHParticlePair((*zIter), (*xIter)));
				}
				++zIter;
			}
		}
	}

	return pairs;
}
