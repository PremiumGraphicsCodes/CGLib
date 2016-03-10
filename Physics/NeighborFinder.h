#ifndef __CRYSTAL_PHYSICS_NEIGHBOR_FINDER_H__
#define __CRYSTAL_PHYSICS_NEIGHBOR_FINDER_H__

#include "ParticlePair.h"
#include "../Polygon/SpaceHash.h"

namespace Crystal {
	namespace Physics {

class NeighborFinder
{
public:
	NeighborFinder(const float divideLength, const int tableSize);

	void add(SPHParticle* particle);

	std::vector<SPHParticlePair> getPairs() const { return pairs; }

private:
	Polygon::SpaceHash spaceHash;
	std::vector<SPHParticlePair> pairs;
};

	}
}
#endif