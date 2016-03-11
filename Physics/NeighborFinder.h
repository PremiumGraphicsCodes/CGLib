#ifndef __CRYSTAL_PHYSICS_NEIGHBOR_FINDER_H__
#define __CRYSTAL_PHYSICS_NEIGHBOR_FINDER_H__

#include "ParticlePair.h"
#include "../Polygon/SpaceHash.h"
#include <array>

namespace Crystal {
	namespace Physics {

class NeighborFinder
{
public:
	NeighborFinder(const float divideLength, const int tableSize);

	void add(SPHParticle* particle);

	void create(const std::vector<SPHParticle*>& particle);

	std::vector<SPHParticlePair> getPairs() const { return pairs; }

private:
	Polygon::SpaceHash spaceHash;
	float divideLength;
	std::vector<SPHParticlePair> pairs;
};

	}
}
#endif