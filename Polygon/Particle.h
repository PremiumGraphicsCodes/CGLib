#ifndef __CRYSTAL_POLYGON_PARTICLE_H__
#define __CRYSTAL_POLYGON_PARTICLE_H__

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Math {
		template<typename>
		class Box;
	}
	namespace Polygon {

class Particle
{
public:
	Particle(const Math::Vector3d<float>& position, const float radius) :
		position(position),
		radius(radius),
		value(0)
	{}

	Particle(const Math::Vector3d<float>& position, const float value, const float radius) :
		position(position),
		radius(radius),
		value(value)
	{}

	Math::Vector3d<float> getPosition() const { return position; }

	Math::Box<float> getBoundingBox() const;

	float getValue() const { return value; }

	Particle* clone() {
		return new Particle(position, value, radius);
	}

	float getRadius() const { return radius; }

	float getDiameter() const { return radius * 2.0f; }

	void addValue(const float v) { this->value += v; }

	bool isCollided(const Particle& rhs);

private:
	Math::Vector3d<float> position;
	float value;
	float radius;
};

	}
}

#endif