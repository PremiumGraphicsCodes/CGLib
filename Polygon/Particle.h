#ifndef __CRYSTAL_POLYGON_PARTICLE_H__
#define __CRYSTAL_POLYGON_PARTICLE_H__

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Math {
		template<typename>
		class Box3d;
	}
	namespace Polygon {

class Particle
{
public:

	Particle(const int id = -1) :
		id(id)
	{}

	Particle(const Math::Vector3d<float>& position, const float density, const float radius, const int id = -1) :
		position(position),
		radius(radius),
		density(density),
		id(id)
	{}

	virtual ~Particle() {}

	void move(const Math::Vector3d<float>& center) { this->position += center; }

	void moveTo(const Math::Vector3d<float>& center) { this->position = center; }

	Particle createBlended(const Particle& rhs, const float ratio) const;

	Math::Vector3d<float> getPosition() const { return position; }

	Math::Box3d<float> getBoundingBox() const;

	float getDensity() const { return density; }

	Particle* clone() const {
		return new Particle(position, density, radius);
	}

	float getRadius() const { return radius; }

	float getDiameter() const { return radius * 2.0f; }

	float getVolume() const { return std::pow(getDiameter(), 3); }

	void addValue(const float v) { this->density += v; }

	bool isCollided(const Particle& rhs);

	bool equals(const Particle& rhs) const;

	bool operator==(const Particle& rhs) const;

	bool operator!=(const Particle& rhs) const;

	void rotate(const Math::Matrix3d<float>& matrix) {
		position.rotate(matrix);
	}

	int getId() const { return id; }

protected:
	float density;


private:
	Math::Vector3d<float> position;
	const int id;
	float radius;
};

	}
}

#endif