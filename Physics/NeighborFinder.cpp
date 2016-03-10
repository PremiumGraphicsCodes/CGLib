#include "NeighborFinder.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

NeighborFinder::NeighborFinder(const float divideLength, const int tableSize) :
	spaceHash(divideLength, tableSize)
{
}

void NeighborFinder::add(SPHParticle* particle)
{
	const auto& neighbors = spaceHash.getNeighbor(particle->getPosition());
	for (const auto& p : neighbors) {
		auto p1 = particle;
		auto p2 = static_cast<SPHParticle*>(p);
		pairs.push_back(SPHParticlePair(p1, p2));
	}
	spaceHash.add(particle);
}
