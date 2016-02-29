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

	float getDistanceSquared() const {
		return particle1->getCenter().getDistanceSquared(particle2->getCenter());
	}

	float getPressure() const {
		return (particle1->getPressure() + particle2->getPressure()) * 0.5f;
	}

	float getViscosityCoe() const {
		return (particle1->getViscosityCoe() + particle2->getViscosityCoe()) * 0.5f;
	}

	Math::Vector3d<float> getVelocityDiff() const {
		return Math::Vector3d<float>(particle1->getVelocity(), particle2->getVelocity());
	}

	bool isValid() const {
		return
			particle1 != nullptr &&
			particle2 != nullptr &&
			particle1 != particle2;
	}

	Particle* getParticle1() const { return particle1; }

	Particle* getParticle2() const { return particle2; }

private:
	Particle* particle1;
	Particle* particle2;
};

using ParticlePairVector = std::vector<ParticlePair>;

	}
}

#endif