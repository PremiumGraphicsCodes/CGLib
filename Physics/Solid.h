#ifndef __CRYSTAL_PHYSICS_SOLID_H__
#define __CRYSTAL_PHYSICS_SOLID_H__

#include "../Math/Box.h"
#include "../Math/Sphere.h"
#include "../Math/Quaternion.h"
#include "../Physics/Particle.h"

#include "../ThirdParty/bullet/src/btBulletDynamicsCommon.h"

namespace Crystal {
	namespace Physics {

class Converter
{
public:

	static btVector3 convert(const Math::Vector3d<float>& src);

	static Math::Vector3d<float> convert(const btVector3& src);

	static Math::Quaternion<float> convert(const btQuaternion& src);

	static btQuaternion convert(const Math::Quaternion<float>& src);
};

class Surfels
{
public:
	Surfels(const Math::Box<float>& box, const float divideLength);

	Surfels(const Math::Sphere<float>& sphere, const float divideLength);

	std::vector<Math::Vector3d<float>> getWorld(const Math::Vector3d<float>& center, const Math::Quaternion<float>& rotation) const;

private:
	std::vector<Math::Vector3d<float>> positions;
};

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