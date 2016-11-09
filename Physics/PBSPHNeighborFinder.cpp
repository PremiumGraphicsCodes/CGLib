#include "PBSPHNeighborFinder.h"
//#include "PBIndexedParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

void PBSPHNeighborFinder::add(const std::vector<PBIndexedParticle>& particles)
{
	iparticles = particles;
	for (auto& particle : iparticles) {
		particle.setGridID(effectLength);
	}
	std::sort(iparticles.begin(), iparticles.end());
}

void PBSPHNeighborFinder::add(const std::vector<PBSPHParticle*>& particles)
{
	for (const auto& particle : particles) {
		iparticles.push_back(PBIndexedParticle(particle));
	}

	for (auto& particle : iparticles) {
		particle.setGridID(effectLength);
	}

	std::sort(iparticles.begin(), iparticles.end());
}

void PBSPHNeighborFinder::createPairs(std::vector<PBSPHParticle*> particles)
{
	if (particles.empty()) {
		return;
	}

	// optimization for quad core.
	const int threads = 8;

	std::vector<std::vector<PBSPHParticlePair>> eachPairs(threads);

	std::vector<std::vector<PBIndexedParticle>::const_iterator> iters;
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

std::vector<PBSPHParticlePair> PBSPHNeighborFinder::search1(const std::vector<PBIndexedParticle>& particles, std::vector<PBIndexedParticle>::const_iterator startIter, std::vector<PBIndexedParticle>::const_iterator endIter, const float effectLengthSquared)
{
	std::vector<PBSPHParticlePair> pairs;
	for (auto xIter = startIter; xIter != endIter; ++xIter) {
		const auto gridID = xIter->getGridID();
		const auto& centerX = xIter->getPosition();
		auto yIter = xIter;
		++yIter;// ignore itself.
		while (yIter != particles.end() && (yIter->getGridID() <= gridID + 1)) {
			const auto& centerY = yIter->getPosition();
			if (centerX.getDistanceSquared(centerY) < effectLengthSquared) {
				pairs.push_back(PBSPHParticlePair(xIter->getParticle(), yIter->getParticle()));
			}
			++yIter;
		}
	}
	return pairs;
}

std::vector<PBSPHParticlePair> PBSPHNeighborFinder::search2(const std::vector<PBIndexedParticle>& particles, std::vector<PBIndexedParticle>::const_iterator startIter, std::vector<PBIndexedParticle>::const_iterator endIter, const float effectLengthSquared)
{
	std::vector<PBSPHParticlePair> pairs;

	std::vector<std::vector<PBIndexedParticle>::const_iterator> yIter(4, startIter);
	std::vector<int> offsetIds;
	offsetIds.push_back(1023);
	offsetIds.push_back(1047551);
	offsetIds.push_back(1048575);
	offsetIds.push_back(1049599);

	for (auto xIter = startIter; xIter != endIter; ++xIter) {
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
					pairs.push_back(PBSPHParticlePair(xIter->getParticle(), zIter->getParticle()));
				}
				++zIter;
			}
		}
	}

	return pairs;
}
