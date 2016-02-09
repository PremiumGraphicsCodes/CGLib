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

	Particle(const Math::Vector3d<float>& position, const float density, const float radius) :
		position(position),
		radius(radius),
		density(density)
	{}

	Particle createBlended(const Particle& rhs, const float ratio) const;

	Math::Vector3d<float> getPosition() const { return position; }

	Math::Box<float> getBoundingBox() const;

	float getDensity() const { return density; }

	Particle* clone() const {
		return new Particle(position, density, radius);
	}

	float getRadius() const { return radius; }

	float getDiameter() const { return radius * 2.0f; }

	void addValue(const float v) { this->density += v; }

	bool isCollided(const Particle& rhs);

private:
	Math::Vector3d<float> position;
	float density;
	float radius;
};

	}
}

#endif