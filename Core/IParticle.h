#ifndef __CRYSTAL_CORE_I_PARTICLE_H__
#define __CRYSTAL_CORE_I_PARTICLE_H__

#include "../Math/Vector3d.h"
#include "../Math/Box3d.h"

namespace Crystal {
	namespace Core {

class IParticle
{
public:
	IParticle(const int id = -1) :
		id(id)
	{}

	IParticle(const Math::Vector3d<float>& position, const float density, const int id = -1) :
		position(position),
		density(density),
		id(id)
	{}

	virtual ~IParticle() = default;

	void move(const Math::Vector3d<float>& center) { this->position += center; }

	void moveTo(const Math::Vector3d<float>& center) { this->position = center; }

	Math::Vector3d<float> getPosition() const { return position; }

	virtual Math::Box3d<float> getBoundingBox() const = 0;

	virtual float getBoundingRadius() const = 0;

	int getId() const { return id; }

	float getDensity() const { return density; }

	virtual Math::Matrix3d<float> getMatrix() const = 0;

protected:
	Math::Vector3d<float> position;
	float density;
	const int id;
};
	}
}

#endif