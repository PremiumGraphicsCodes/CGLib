#ifndef __CRYSTAL_PHYSICS_BUBBLE_PARTICLE_H__
#define __CRYSTAL_PHYSICS_BUBBLE_PARTICLE_H__

#include "../Math/Vector3d.h"
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

	BubbleParticle(const Math::Vector3d<float>& position, const Math::Vector3d<float>& velocity, const Math::Vector3d<float>& normal, const float mass) :
		position(position),
		velocity(velocity),
		normal(normal),
		mass(mass)
	{}

	void setNeighbors(const std::list<BubbleParticle*>& neighbors) { this->neighbors = neighbors; }

	float getCurvature(const BubbleParticle& rhs, const float effectRadius) const;

	float getTrappedAirPotential(const BubbleParticle& rhs, const float effectRadius) const;

	float getWeight(const float distance, const float effectRadius) const;

	float getMovingDirectionCoe() const;

	float getMovingDelta() const;

	float getKineticEnegy() const;

	void solveTrappedAirPotential(const float effectRadius);

	void solveWaveCrestPotential(const float effectRadius);

	void solveKineticEnergy();

	float getGenerateParticleNumber(const float trappedAirCoe, const float waveCrestCoe, const float dt) const;

	Type getType() const;

private:
	Math::Vector3d<float> position;
	Math::Vector3d<float> velocity;
	Math::Vector3d<float> normal;
	float mass;
	float effectRadius;

	float totalTrappedAirPotential;

	float totalWaveCrestPotential;

	float kineticEnergyPotential;

	std::list<BubbleParticle*> neighbors;

private:
	Math::Vector3d<float> getNormalizedDistance(const BubbleParticle& rhs) const;

	Math::Vector3d<float> getNormalizedVelocity(const BubbleParticle& rhs) const;

	float getDistance(const BubbleParticle& rhs) const;

};

	}
}

#endif