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
	Joint(const Math::Vector3d<float>& pos, const unsigned int id = -1) :
		position(pos),
		id(id)
	{}

	unsigned int getId() const { return id; }

	Particle toParticle(const float radius, const float density) const;

	Math::Vector3d<float> getPosition() const { return position; }

private:
	Math::Vector3d<float> position;
	const unsigned int id;
};

	}
}

#endif