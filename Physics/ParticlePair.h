#ifndef __CRYSTAL_PHYSICS_SPH_PARTICLE_PAIR_H__
#define __CRYSTAL_PHYSICS_SPH_PARTICLE_PAIR_H__

#include "SPHParticle.h"

namespace Crystal {
	namespace Physics {

class SPHParticlePair final
{
public:
	SPHParticlePair();

	SPHParticlePair(SPHParticle* particle1, SPHParticle* particle2);

	Math::Vector3d<float> getDistanceVector() const;

	float getDistance() const;

	float getDistanceSquared() const;

	float getPressure() const;

	void solveDensity();

	void solvePressureForce();

	void solveViscosityForce();

	Math::Vector3d<float> getVelocityDiff() const;

	bool isValid() const;

	SPHParticle* getParticle1() const { return particle1; }

	SPHParticle* getParticle2() const { return particle2; }

private:
	SPHParticle* particle1;
	SPHParticle* particle2;
};

	}
}

#endif