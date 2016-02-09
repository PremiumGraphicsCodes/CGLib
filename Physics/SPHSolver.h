#ifndef __CRYSTAL_PHYSICS_SPH_SOLVER_H__
#define __CRYSTAL_PHYSICS_SPH_SOLVER_H__

#include "Particle.h"
#include "PhysicsObject.h"
#include "PhysicsParticleFindAlgo.h"
#include "Coordinator.h"
#include "../Math/Tolerance.h"

#ifdef _OPENMP
#include <omp.h>
#endif


namespace Crystal{
	namespace Physics{

template<typename GeomType = float>
class SPHSolver
{
public:
	void solve(const std::vector< PhysicsObject<GeomType> >& objects, const GeomType effectLength);

private:
	std::vector<Particle*> getParticles(const std::vector< PhysicsObject<GeomType> >& objects) {
		std::vector<Particle*> ordered;
		for (const auto& object : objects) {
			const auto& particles = object.getParticles();
			ordered.insert(ordered.end(), particles.begin(), particles.end());
		}
		return ordered;
	}

};

	}
}

#endif