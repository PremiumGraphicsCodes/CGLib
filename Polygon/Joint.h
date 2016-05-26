#ifndef __CRYSTAL_POLYGON_JOINT_H__
#define __CRYSTAL_POLYGON_JOINT_H__

#include "../Math/Vector3d.h"
#include "Particle.h"

namespace Crystal {
	namespace Core {
		class Particle;

class Joint
{
public:
	Joint(const Math::Vector3d<float>& pos, const float radius, const unsigned int id = -1) :
		position(pos),
		radius(radius),
		id(id)
	{}

	unsigned int getId() const { return id; }

	Particle toParticle(const float density) const;

	Math::Vector3d<float> getPosition() const { return position; }

	void scale(const float s) { this->radius += s; }

	void move(const Math::Vector3d<float>& v) { this->position += v; }

	float getRadius() const { return radius; }

	float getDiameter() const { return radius * 2.0f; }


private:
	Math::Vector3d<float> position;
	float radius;
	const unsigned int id;
};

	}
}

#endif