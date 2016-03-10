#ifndef __CRYSTAL_PHYSICS_BULLET_RIGID_H__
#define __CRYSTAL_PHYSICS_BULLET_RIGID_H__

#include <vector>

#include "Bullet.h"

#include "../Math/Box.h"
#include "../Math/Sphere.h"
#include "../Math/Quaternion.h"
#include "Surfels.h"

class btRigidBody;

namespace Crystal {
	namespace Physics {
		class Particle;

class BulletRigid
{
public:
	BulletRigid(const Math::Box<float>& box, const float mass);

	BulletRigid(const Math::Sphere<float>& sphere, const float mass);

	BulletRigid(btRigidBody* body) :
		body(body)
	{}

	float getMass() const;

	bool isDynamic() const;

	bool isStatic() const;

	Math::Vector3d<float> getOrigin() const;

	Math::Quaternion<float> getOrientation() const;

	Surfels toSurlfes(const float divideLength) const;

private:
	btRigidBody* body;
	Math::Box<float> localBox;
};

	}
}

#endif