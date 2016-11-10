#ifndef __CRYSTAL_PHYSICS_BUBBLE_PARTICLE_H__
#define __CRYSTAL_PHYSICS_BUBBLE_PARTICLE_H__

#include "../Math/Vector3d.h"
#include <list>

namespace Crystal {
	namespace Physics {

class BubbleParticle
{
public:
	BubbleParticle(const Math::Vector3d<float>& position, const Math::Vector3d<float>& velocity, const Math::Vector3d<float>& normal) :
		position(position),
		velocity(velocity),
		normal(normal)
	{}

	void setNeighbors(const std::list<BubbleParticle*>& neighbors) { this->neighbors = neighbors; }

	float getCurvature(const BubbleParticle& rhs, const float effectRadius) const;

	float getTrappedAirPotential(const BubbleParticle& rhs, const float effectRadius) const;

	float getWeight(const float distance, const float effectRadius) const;

	float getMovingDirectionCoe() const;

	float getMovingDelta() const;

	float getKineticEnegy(const float mass) const;

	void solveTrappedAirPotential(const float effectRadius);

	void solveCrestPotential(const float effectRadius);

private:
	Math::Vector3d<float> position;
	Math::Vector3d<float> velocity;
	Math::Vector3d<float> normal;
	float effectRadius;

	float totalTrappedAirPotential;

	float totalCrestPotential;

	std::list<BubbleParticle*> neighbors;

private:
	Math::Vector3d<float> getNormalizedDistance(const BubbleParticle& rhs) const;

	Math::Vector3d<float> getNormalizedVelocity(const BubbleParticle& rhs) const;

	float getDistance(const BubbleParticle& rhs) const;

};

	}
}

#endif