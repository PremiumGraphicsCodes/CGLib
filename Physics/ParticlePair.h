#ifndef __CRYSTAL_PHYSICS_PARTICLE_PAIR_H__
#define __CRYSTAL_PHYSICS_PARTICLE_PAIR_H__

#include "Particle.h"

namespace Crystal {
	namespace Physics {

template<typename T>
class ParticlePair final
{
public:
	ParticlePair() :
		particle1( nullptr ),
		particle2( nullptr )
	{}

	ParticlePair(const ParticleSPtr<T>& particle1, const ParticleSPtr<T>& particle2) :
		particle1(particle1),
		particle2(particle2)
	{
	}

	Math::Vector3d<T> getDistanceVector() const {
		return Math::Vector3d<T>(particle1->getCenter() - particle2->getCenter());
	}

	float getDistance() const {
		return getDistanceVector().getLength();
	}

	float getDistanceSquared() const {
		return particle1->getCenter().getDistanceSquared(particle2->getCenter());
	}

	float getPressure() const {
		return (particle1->getPressure() + particle2->getPressure()) * 0.5f;
	}

	float getViscosityCoe() const {
		return (particle1->getViscosityCoe() + particle2->getViscosityCoe()) * 0.5f;
	}

	Math::Vector3d<T> getVelocityDiff() const {
		return Math::Vector3d<T>(particle1->getVelocity(), particle2->getVelocity());
	}

	bool isValid() const {
		return
			particle1 != nullptr &&
			particle2 != nullptr &&
			particle1 != particle2;
	}

	ParticleSPtr<T> getParticle1() const { return particle1; }

	ParticleSPtr<T> getParticle2() const { return particle2; }

private:
	ParticleSPtr<T> particle1;
	ParticleSPtr<T> particle2;
};

using ParticlePairVector = std::vector<ParticlePair<float> >;

	}
}

#endif