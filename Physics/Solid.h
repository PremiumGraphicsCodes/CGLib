#ifndef __CRYSTAL_PHYSICS_SOLID_H__
#define __CRYSTAL_PHYSICS_SOLID_H__

#include "../Math/Box.h"
#include "../Math/Sphere.h"
#include "../Math/Quaternion.h"
#include "../Physics/Particle.h"

#include "../ThirdParty/bullet/src/btBulletDynamicsCommon.h"
#include "Surfels.h"

namespace Crystal {
	namespace Physics {

class Solid
{
public:

	Solid(const Math::Box<float>& box, const float mass);

	Solid(const Math::Sphere<float>& sphere, const float mass);

	float getMass() const;

	bool isDynamic() const;

	bool isStatic() const;

	Math::Vector3d<float> getOrigin() const;

	Math::Quaternion<float> getOrientation() const;

	std::vector<Math::Vector3d<float>> getWorldSurfels();

private:
	std::vector<Math::Vector3d<float>> localSurfels;
	btRigidBody* body;
};

	}
}

#endif