#include "NeighborFinder.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

NeighborFinder::NeighborFinder(const float divideLength, const int tableSize) :
	spaceHash(divideLength, tableSize),
	divideLength(divideLength)
{
}

void NeighborFinder::add(SPHParticle* particle)
{
	spaceHash.add(particle);
}

void NeighborFinder::create(const std::vector<SPHParticle*>& particles)
{
	if (spaceHash.isEmpty()) {
		return;
	}
	constexpr int threads = 8;
	std::array< std::vector<SPHParticlePair>, threads> tpairs;
	std::array< int, threads > starts;
	std::array< int, threads > ends;
	for (int i = 0; i < threads; ++i) {
		starts[i] = (particles.size() / threads) * (i);
		ends[i] = (particles.size() / threads) * (i + 1);
	}
	ends[threads - 1] = particles.size();
#pragma omp parallel for
	for (int i = 0; i < threads; ++i) {
		for (int j = starts[i]; j < ends[i]; ++j) {
			const auto particle = particles[j];
			const auto& neighbors = spaceHash.getNeighbor(particle->getPosition(), divideLength);
			for (const auto& p : neighbors) {
				auto p1 = static_cast<SPHParticle*>(p);
				auto p2 = particle;
				if (p1 == p2) {
					continue;
				}
				if (p1 < p2) {
					tpairs[i].push_back(SPHParticlePair(p1, p2));
					//tpairs[i].push_back(SPHParticlePair(p2, p1));
				}
			}
		}
	}
	for (int i = 0; i < tpairs.size(); ++i) {
		pairs.insert(pairs.end(), tpairs[i].begin(), tpairs[i].end());
	}
}



template<typename GeomType>
void ParticleFindAlgo<GeomType>::createPairs(std::vector<SPHParticle*> particles, const GeomType effectLength)
{
	if (particles.empty()) {
		return;
	}

	for (const auto& particle : particles) {
		particle->setGridID(effectLength);
	}

	std::sort(particles.begin(), particles.end(), &SPHParticle::compare);

	// optimization for quad core.
	const int threads = 8;

	std::vector<std::vector<SPHParticlePair>> eachPairs(threads);

	std::vector<std::vector<SPHParticle*>::const_iterator> iters;
	for (int i = 0; i < threads; ++i) {
		iters.push_back(particles.begin() + i * particles.size() / threads);
	}
	iters.push_back(particles.end());

#pragma omp parallel for
	for (int i = 0; i < threads; ++i) {
		eachPairs[i] = search1(particles, iters[i], iters[i + 1], effectLength * effectLength);
	}

	for (size_t i = 0; i < eachPairs.size(); ++i) {
		pairs.insert(pairs.end(), eachPairs[i].begin(), eachPairs[i].end());
	}

#pragma omp parallel for
	for (int i = 0; i < threads; ++i) {
		eachPairs[i] = search2(particles, iters[i], iters[i + 1], effectLength * effectLength);
	}

	for (size_t i = 0; i < eachPairs.size(); ++i) {
		pairs.insert(pairs.end(), eachPairs[i].begin(), eachPairs[i].end());
	}
}

template<typename GeomType>
std::vector<SPHParticlePair> ParticleFindAlgo<GeomType>::search1(const std::vector<SPHParticle*>& particles, std::vector<SPHParticle*>::const_iterator startIter, std::vector<SPHParticle*>::const_iterator endIter, const float effectLengthSquared)
{
	std::vector<SPHParticlePair> pairs;
	for (auto xIter = startIter; xIter != endIter; ++xIter) {
		const auto gridID = (*xIter)->getGridID();
		const auto& centerX = (*xIter)->getPosition();
		auto yIter = xIter;
		++yIter;// ignore itself.
		while (yIter != particles.end() && ((*yIter)->getGridID() <= gridID + 1)) {
			const auto& centerY = (*yIter)->getPosition();
			if (centerX.getDistanceSquared(centerY) < effectLengthSquared) {
				if ((*xIter)->isBoundary() && (*yIter)->isBoundary()) {
					++yIter;
					continue;
				}
				pairs.push_back(SPHParticlePair((*xIter), (*yIter)));
				//pairs.push_back(SPHParticlePair((*yIter), (*xIter)));
			}
			++yIter;
		}
	}
	return pairs;
}

template<typename GeomType>
std::vector<SPHParticlePair> ParticleFindAlgo<GeomType>::search2(const std::vector<SPHParticle*>& particles, std::vector<SPHParticle*>::const_iterator startIter, std::vector<SPHParticle*>::const_iterator endIter, const float effectLengthSquared)
{
	std::vector<SPHParticlePair> pairs;

	std::vector<std::vector<SPHParticle*>::const_iterator> yIter(4, startIter);
	std::vector<int> offsetIds;
	offsetIds.push_back(1023);
	offsetIds.push_back(1047551);
	offsetIds.push_back(1048575);
	offsetIds.push_back(1049599);

	for (std::vector<SPHParticle*>::const_iterator xIter = startIter; xIter != endIter; ++xIter) {
		for (size_t i = 0; i < 4; ++i) {
			const auto baseID = (*xIter)->getGridID() + offsetIds[i];
			while (yIter[i] != particles.end() && ((*yIter[i])->getGridID() < baseID)) {
				++yIter[i];
			}

			const auto& centerX = (*xIter)->getPosition();
			auto zIter = yIter[i];
			while (zIter != particles.end() && ((*zIter)->getGridID() <= baseID + 2)) {
				const auto& centerZ = (*zIter)->getPosition();
				if (centerX.getDistanceSquared(centerZ) < effectLengthSquared) {
					if ((*xIter)->isBoundary() && (*zIter)->isBoundary()) {
						++zIter;
						continue;
					}
					pairs.push_back(SPHParticlePair((*xIter), (*zIter)));
					//pairs.push_back(SPHParticlePair((*zIter), (*xIter)));
				}
				++zIter;
			}
		}
	}

	return pairs;

}



template class ParticleFindAlgo<float>;