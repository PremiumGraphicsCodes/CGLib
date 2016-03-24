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
