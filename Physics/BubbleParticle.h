#ifndef __CRYSTAL_PHYSICS_BUBBLE_PARTICLE_H__
#define __CRYSTAL_PHYSICS_BUBBLE_PARTICLE_H__

#include "../Math/Vector3d.h"
#include "PBSPHParticle.h"
#include <list>

namespace Crystal {
	namespace Physics {

class BubbleParticle
{
public:
	enum class Type {
		Spray,
		Air,
		Foam,
	};

	BubbleParticle(PBSPHParticle* parent) :
		parent(parent)
	{}

	std::list<PBSPHParticle*> getNeighbors() const { return parent->getNeighbors(); }

	float getEffectLength() const { return parent->getEffectLength(); }

	Math::Vector3d<float> getVelocity() const { return parent->getVelocity(); }

	float getCurvature(const PBSPHParticle& rhs, const float effectRadius) const;

	float getTrappedAirPotential(const PBSPHParticle& rhs, const float effectRadius) const;

	float getWeight(const float distance, const float effectRadius) const;

	float getMovingDirectionCoe() const;

	float getMovingDelta() const;

	float getKineticEnegy() const;

	void solveTrappedAirPotential(const float effectRadius);

	void solveWaveCrestPotential(const float effectRadius);

	void solveKineticEnergy();

	float getGenerateParticleNumber(const float trappedAirCoe, const float waveCrestCoe, const float dt) const;

	Type getType() const;

	float getMass() const { return parent->getMass(); }

private:
	PBSPHParticle* parent;

	float totalTrappedAirPotential;

	float totalWaveCrestPotential;

	float kineticEnergyPotential;

private:
	Math::Vector3d<float> getPosition() const { return parent->getPosition(); }

	Math::Vector3d<float> getNormal() const { return parent->getNormal(); }

	Math::Vector3d<float> getNormalizedDistance(const PBSPHParticle& rhs) const;

	Math::Vector3d<float> getNormalizedVelocity(const PBSPHParticle& rhs) const;

	float getDistance(const PBSPHParticle& rhs) const;

};

	}
}

#endif