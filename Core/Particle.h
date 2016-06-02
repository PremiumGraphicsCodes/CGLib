#ifndef __CRYSTAL_POLYGON_PARTICLE_H__
#define __CRYSTAL_POLYGON_PARTICLE_H__

#include "IParticle.h"

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Math {
		template<typename>
		class Box3d;
	}
	namespace Core {

class Particle : public IParticle
{
public:

	Particle(const int id = -1);

	Particle(const Math::Vector3d<float>& position, const float density, const float radius, const int id = -1);

	virtual ~Particle() {}

	Particle createBlended(const Particle& rhs, const float ratio) const;

	Math::Box3d<float> getBoundingBox() const override;

	Particle* clone() const {
		return new Particle(position, density, radius);
	}

	float getBoundingRadius() const override { return radius; }

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

private:
	float radius;
};

	}
}

#endif