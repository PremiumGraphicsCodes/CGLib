#ifndef __CRYSTAL_PHYSICS_BULLET_RIGID_H__
#define __CRYSTAL_PHYSICS_BULLET_RIGID_H__

#include <vector>

#include "Bullet.h"

#include "../Math/Vector3d.h"
#include "../Math/Box.h"
#include "../Math/Sphere.h"
#include "../Math/Quaternion.h"
#include "Surfels.h"

class btRigidBody;

namespace Crystal {
	namespace Physics {
		class SPHParticle;

class BulletRigid
{
public:
	BulletRigid(const Math::Vector3d<float>& length, const Math::Vector3d<float>& origin, const float mass);

	//BulletRigid(const Math::Sphere<float>& sphere, const float mass);

	BulletRigid(btRigidBody* body) :
		body(body)
	{}

	~BulletRigid();

	void clear();

	float getMass() const;

	bool isDynamic() const;

	bool isStatic() const;

	Math::Vector3d<float> getOrigin() const;

	Math::Quaternion<float> getOrientation() const;

	Surfels toSurlfes(const float divideLength) const;

	btRigidBody* getBody() const { return body; }

	void transform();

	std::vector<SPHParticle*> getSurfaceParticles();

private:
	btRigidBody* body;
	Math::Box<float> localBox;
	std::vector<Math::Vector3d<float>> positions;
	std::vector<SPHParticle*> sampleParticles;
};

	}
}

#endif