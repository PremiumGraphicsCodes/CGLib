#ifndef __CRYSTAL_PHYSICS_BUBBLE_PARTICLE_H__
#define __CRYSTAL_PHYSICS_BUBBLE_PARTICLE_H__

#include "../Math/Vector3d.h"
#include "PBSPHParticle.h"
#include <list>

namespace Crystal {
	namespace Physics {
		class ITinyParticle;

class BubbleParticle
{
public:
	enum class Type {
		Spray,
		Air,
		Foam,
	};

	BubbleParticle(PBSPHParticle* parent);

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

	void clampTrappedAirPotential(const float min_ = 5.0f, const float max_ = 20.0f);

	void solveWaveCrestPotential(const float effectRadius);

	void clampWaveCrestPotential(const float min_ = 2.0f, const float max_ = 8.0f);

	void solveKineticEnergy();

	void clampKineticEnegyPotential(const float min_ = 5.0f, const float max_ = 50.0f);

	float getGenerateParticleNumber(const float trappedAirCoe, const float waveCrestCoe, const float dt) const;

	std::list<ITinyParticle*> generateTinyParticles(const int howMany);

	Type getType() const;

	float getMass() const;

	float getTotalTrappedAirPotential() const { return totalTrappedAirPotential; }

	float getTotalWeveCrestPotential() const { return totalWaveCrestPotential; }

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