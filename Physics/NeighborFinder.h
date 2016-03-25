#ifndef __CRYSTAL_PHYSICS_NEIGHBOR_FINDER_H__
#define __CRYSTAL_PHYSICS_NEIGHBOR_FINDER_H__

#include "ParticlePair.h"
#include "../Polygon/SpaceHash.h"
#include <array>

#include "IndexedParticle.h"
#include <vector>


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


class ParticleFindAlgo final : private UnCopyable {
public:
	ParticleFindAlgo(const float effectLength) :
		effectLength(effectLength)
	{}

	void add(const std::vector<SPHParticle*>& particles);

	void createPairs(std::vector<SPHParticle*> particles);

	std::vector<SPHParticlePair> getPairs() const { return pairs; }

private:
	std::vector<SPHParticlePair> pairs;

	std::vector<SPHParticlePair> search1(const std::vector<IndexedParticle>& particles, std::vector<IndexedParticle>::const_iterator startIter, std::vector<IndexedParticle>::const_iterator endIter, const float effectLengthSquared);

	std::vector<SPHParticlePair> search2(const std::vector<IndexedParticle>& particles, std::vector<IndexedParticle>::const_iterator startIter, std::vector<IndexedParticle>::const_iterator endIter, const float effectLengthSquared);

	std::vector<IndexedParticle> iparticles;
	const float effectLength;
};
	}
}
#endif