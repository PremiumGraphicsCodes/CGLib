#ifndef __CRYSTAL_PHYSICS_SOLID_H__
#define __CRYSTAL_PHYSICS_SOLID_H__

#include "../Math/Box.h"
#include "../Math/Sphere.h"

#include "../ThirdParty/bullet/src/btBulletDynamicsCommon.h"

namespace Crystal {
	namespace Physics {

class IRigid
{
public:
	btRigidBody* body;

	virtual Math::Vector3d<float> getSurfels() = 0;

private:
	Math::Vector3d<float> surfels;
};

class DynamicRigid : public IRigid
{
public:
	DynamicRigid(const Math::Box<float>& box, const float mass);

	DynamicRigid(const Math::Sphere<float>& sphere, const float mass);

private:
	const float mass;
	btVector3 inertia;
};

class StaticRigid : public IRigid
{
public:
	StaticRigid(const Math::Box<float>& box);

	StaticRigid(const Math::Sphere<float>& sphere);

private:

};

class RigidWorld
{
public:
	void add(IRigid* rigid) { world->addRigidBody(rigid->body); }

	void simulate(const float timeStep);


private:
	std::vector< IRigid*> rigids;
	btDynamicsWorld* world;
};
	}
}

#endif