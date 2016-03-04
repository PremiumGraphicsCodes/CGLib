#ifndef __CRYSTAL_PHYSICS_PARTICLE_PAIR_H__
#define __CRYSTAL_PHYSICS_PARTICLE_PAIR_H__

#include "Particle.h"

namespace Crystal {
	namespace Physics {

class ParticlePair final
{
public:
	ParticlePair();

	ParticlePair(Particle* particle1, Particle* particle2);

	Math::Vector3d<float> getDistanceVector() const;

	float getDistance() const;

	float getDistanceSquared() const;

	float getPressure() const;

	float getViscosityCoe() const;

	Math::Vector3d<float> getVelocityDiff() const;

	bool isValid() const;

	Particle* getParticle1() const { return particle1; }

	Particle* getParticle2() const { return particle2; }

private:
	Particle* particle1;
	Particle* particle2;
};

	}
}

#endif