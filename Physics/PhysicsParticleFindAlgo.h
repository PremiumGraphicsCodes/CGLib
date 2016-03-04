#ifndef __CRYSTAL_PHYSICS_PARTICLE_FIND_ALGO_H__
#define __CRYSTAL_PHYSICS_PARTICLE_FIND_ALGO_H__

#include "Particle.h"
#include "ParticlePair.h"

#include "../Util/UnCopyable.h"

#include <vector>
#include <algorithm>

#ifdef _OPENMP
#include <omp.h>
#endif


namespace Crystal{
	namespace Physics{

template<typename GeomType>
class ParticleFindAlgo final : private UnCopyable{
public:
	ParticleFindAlgo() = default;

	~ParticleFindAlgo() = default;

	void createPairs(std::vector<Particle*> particles, const GeomType effectLength);

	std::vector<ParticlePair> getPairs() const { return pairs; }

private:
	std::vector<ParticlePair> pairs;

	std::vector<ParticlePair> search1(const std::vector<Particle*>& particles, std::vector<Particle*>::const_iterator startIter, std::vector<Particle*>::const_iterator endIter, const float effectLengthSquared);

	std::vector<ParticlePair> search2(const std::vector<Particle*>& particles, std::vector<Particle*>::const_iterator startIter, std::vector<Particle*>::const_iterator endIter, const float effectLengthSquared);

};

	}
}

#endif