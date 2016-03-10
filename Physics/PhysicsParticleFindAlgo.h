#ifndef __CRYSTAL_PHYSICS_PARTICLE_FIND_ALGO_H__
#define __CRYSTAL_PHYSICS_PARTICLE_FIND_ALGO_H__

#include "SPHParticle.h"
#include "ParticlePair.h"

#include "../Util/UnCopyable.h"

#include <vector>
#include <algorithm>

#ifdef _OPENMP
#include <omp.h>
#endif

#include "../Polygon/SpaceHash.h"


namespace Crystal{
	namespace Physics{

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

template<typename GeomType>
class ParticleFindAlgo final : private UnCopyable{
public:
	ParticleFindAlgo() = default;

	~ParticleFindAlgo() = default;

	void createPairs(std::vector<SPHParticle*> particles, const GeomType effectLength);

	std::vector<SPHParticlePair> getPairs() const { return pairs; }

private:
	std::vector<SPHParticlePair> pairs;

	std::vector<SPHParticlePair> search1(const std::vector<SPHParticle*>& particles, std::vector<SPHParticle*>::const_iterator startIter, std::vector<SPHParticle*>::const_iterator endIter, const float effectLengthSquared);

	std::vector<SPHParticlePair> search2(const std::vector<SPHParticle*>& particles, std::vector<SPHParticle*>::const_iterator startIter, std::vector<SPHParticle*>::const_iterator endIter, const float effectLengthSquared);

};

	}
}

#endif