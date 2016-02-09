#ifndef __CRYSTAL_POLYGON_JOINT_H__
#define __CRYSTAL_POLYGON_JOINT_H__

#include "../Math/Vector3d.h"
#include "Particle.h"

namespace Crystal {
	namespace Polygon {
		class Particle;

class Joint
{
public:
	Joint(const Math::Vector3d<float>& pos, const float radius, const float density) :
		position(pos),
		radius(radius),
		density(density)
	{}

	Particle toParticle() const;

	Math::Vector3d<float> getPosition() const { return position; }

private:
	Math::Vector3d<float> position;
	float radius;
	float density;
};

	}
}

#endif