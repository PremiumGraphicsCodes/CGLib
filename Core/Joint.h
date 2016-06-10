#ifndef __CRYSTAL_POLYGON_JOINT_H__
#define __CRYSTAL_POLYGON_JOINT_H__

#include "../Math/Vector3d.h"
#include "../Math/Ellipsoid.h"
#include "Particle.h"

namespace Crystal {
	namespace Core {
		class Particle;

class Joint
{
public:
	Joint(const Math::Vector3d<float>& pos, const Math::Vector3d<float>& radii, const unsigned int id = -1) :
		position(pos),
		radii(radii),
		id(id)
	{}

	Joint* clone(const unsigned int newId) const;

	void changeId(const unsigned int newId) { this->id = newId; }

	unsigned int getId() const { return id; }

	AnisotoropicParticle toParticle(const float density) const;

	Math::Vector3d<float> getPosition() const { return position; }

	void scale(const Math::Vector3d<float>& s) { this->radii += s; }

	void move(const Math::Vector3d<float>& v) { this->position += v; }

	Math::Vector3d<float> getRadii() const { return radii; }

	//float getDiameter() const { return radius * 2.0f; }

	float getBoundingRadius() const {
		return std::max<float>({ radii.getX(), radii.getY(), radii.getZ() });
	}

	Math::Ellipsoid<float> toEllipsoid() const;

private:
	Math::Vector3d<float> position;
	Math::Vector3d<float> radii;
	unsigned int id;
};

	}
}

#endif