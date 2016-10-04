#ifndef __CRYSTAL_PHYSICS_ORIENTED_PARTICLE_H__
#define __CRYSTAL_PHYSICS_ORIENTED_PARTICLE_H__

#include <list>
#include "../Math/Matrix3d.h"
#include "../Core/IParticle.h"

namespace Crystal {
	namespace Physics {

class OrientedParticle
{
public:
	OrientedParticle(const Math::Vector3d<float>& position, const float radius) :
		position(position),
		radius(radius)
	{}

	void setNeighbors(const std::list<Core::IParticle*>& neighbors) {
		this->neighbors = neighbors;
	}

	Math::Matrix3d<float> getCovarianceMatrix() const;

	Math::Vector3d<float> getWeightedMeanPosition() const;

	float getTotalWeight() const;

	float getWeight(Core::IParticle* particle) const;

private:
	Math::Vector3d<float> position;
	float radius;
	std::list<Core::IParticle*> neighbors;
};
	}
}

#endif