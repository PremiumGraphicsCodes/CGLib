#include "Solid.h"

#include "../Math/Box.h"
#include "../Math/Quaternion.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

DynamicRigid::DynamicRigid(const Box<float>& box, const float mass):
	mass(mass)
{
	const auto length = box.getLength() * 0.5;
	btVector3 v(length.getX(), length.getY(), length.getZ());
	auto shape = new btBoxShape(v);

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(box.getMinX(), box.getMinY(), box.getMinZ()));

	transform.getOrigin();
	//Quaternion<float> rotation(transform.getRotation().getX(), transform.getRotation().getY(), transform.getRotation().getZ(), transform.getRotation().getW());
	//rotation.toMatrix()

	shape->calculateLocalInertia(mass, inertia);
};

DynamicRigid::DynamicRigid(const Sphere<float>& sphere, const float mass) :
	mass(mass)
{
	const auto center = sphere.getCenter();
	const auto originx = center.getX() - sphere.getRadius();
	const auto originy = center.getY() - sphere.getRadius();
	const auto originz = center.getZ() - sphere.getRadius();

	auto shape = new btSphereShape(sphere.getRadius());

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(btVector3(originx, originy, originz));
}

void RigidWorld::simulate(const float dt)
{
	world->stepSimulation(dt, 10);
	//world-
}