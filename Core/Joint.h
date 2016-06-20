#ifndef __CRYSTAL_POLYGON_JOINT_H__
#define __CRYSTAL_POLYGON_JOINT_H__

#include "../Math/Vector3d.h"
#include "../Math/PolarCoord3d.h"
#include "../Math/Ellipsoid.h"
#include "Particle.h"
#include "UID.h"

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

	UID getUID() const { return UID(id, UID::Type::Joint); }

	AnisotoropicParticle toParticle(const float density) const;

	Math::Vector3d<float> getPosition() const { return position; }

	void scale(const Math::Vector3d<float>& s) { this->radii += s; }

	void move(const Math::Vector3d<float>& v) { this->position += v; }

	void moveTo(const Math::Vector3d<float>& v) { this->position = v; }

	void setRadii(const Math::Vector3d<float>& v) { this->radii = v; }

	Math::Vector3d<float> getRadii() const { return radii; }

	//float getDiameter() const { return radius * 2.0f; }

	float getBoundingRadius() const {
		return std::max<float>({ radii.getX(), radii.getY(), radii.getZ() });
	}

	Math::Ellipsoid<float> toEllipsoid() const;

	//Math::PolarCoord3d<float> getPolarCoord() const { return angle; }

	Math::Quaternion<float> getOrientation() const { return orientation; }

	void setOrientation(const Math::PolarCoord3d<float>& coord) { this->orientation = coord.getOrientation(); }

	void rotate(const Math::Quaternion<float>& q) { this->orientation *= q; }

private:
	Math::Vector3d<float> position;
	Math::Vector3d<float> radii;
	Math::Quaternion<float> orientation;
	unsigned int id;
};

	}
}

#endif