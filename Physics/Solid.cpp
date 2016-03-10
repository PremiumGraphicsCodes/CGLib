#include "Solid.h"

#include "../Math/Box.h"
#include "../Math/Quaternion.h"

#include "BulletConverter.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;





Solid::Solid(const Box<float>& box, const float mass)
{
	const auto length = box.getLength() * 0.5;
	auto shape = new btBoxShape( BulletConverter::convert(length) );

	btTransform transform;
	transform.setIdentity();
	transform.setOrigin( BulletConverter::convert(box.getMin() ) );

	btVector3 inertia;
	shape->calculateLocalInertia(mass, inertia);

	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motionState, shape, inertia);
	body = new btRigidBody(info);

	//box.getMin
};

Solid::Solid(const Sphere<float>& sphere, const float mass)
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

float Solid::getMass() const
{
	return 1.0f / (body->getInvMass());
}

bool Solid::isDynamic() const
{
	return getMass() != 0.0f;
}

bool Solid::isStatic() const
{
	return getMass() == 0.0f;
}

Vector3d<float> Solid::getOrigin() const
{
	btTransform transform;
	body->getMotionState()->getWorldTransform(transform);
	return BulletConverter::convert( transform.getOrigin() );
}

Quaternion<float> Solid::getOrientation() const
{
	return BulletConverter::convert(body->getOrientation());
}

//Mat