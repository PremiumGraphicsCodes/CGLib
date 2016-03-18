#include "BulletRigid.h"

#include "Bullet.h"
#include "BulletConverter.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

BulletRigid::BulletRigid(const Box<float>& box, const float mass)
{
	const auto length = box.getLength();
	auto shape = new btBoxShape(BulletConverter::convert(length));
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin(BulletConverter::convert(box.getMin()));

	btVector3 inertia;
	shape->calculateLocalInertia(mass, inertia);

	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motionState, shape, inertia);
	body = new btRigidBody(info);

	localBox = box;
	//box.getMin
};

BulletRigid::BulletRigid(const Sphere<float>& sphere, const float mass)
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

float BulletRigid::getMass() const
{
	return 1.0f / (body->getInvMass());
}

bool BulletRigid::isDynamic() const
{
	return getMass() != 0.0f;
}

bool BulletRigid::isStatic() const
{
	return getMass() == 0.0f;
}

Vector3d<float> BulletRigid::getOrigin() const
{
	btTransform transform;
	body->getMotionState()->getWorldTransform(transform);
	return BulletConverter::convert(transform.getOrigin());
}

Quaternion<float> BulletRigid::getOrientation() const
{
	return BulletConverter::convert(body->getOrientation());
}

Surfels BulletRigid::toSurlfes(const float divideLength) const
{
	const auto translate = BulletConverter::convert( body->getWorldTransform().getOrigin() );
	const auto rotation = BulletConverter::convert(body->getWorldTransform().getRotation());
	body->getWorldTransform().getRotation();

	Surfels surfels(localBox, divideLength);
	surfels.getWorld(translate, rotation);
	return surfels;
}
