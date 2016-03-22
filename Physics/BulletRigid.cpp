#include "BulletRigid.h"

#include "Bullet.h"
#include "BulletConverter.h"
#include "SPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

BulletRigid::BulletRigid(const Vector3d<float>& length, const Vector3d<float>& origin, const float mass)
{
	auto shape = new btBoxShape(BulletConverter::convert(length));
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin( BulletConverter::convert(origin) );

	btVector3 inertia;
	shape->calculateLocalInertia(mass, inertia);

	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motionState, shape, inertia);
	body = new btRigidBody(info);

	if (mass != 0.0f) {
		for (auto x = -length.getX(); x < length.getX(); x += 1.0f) {
			for (auto y = - length.getY(); y < length.getY(); y += 1.0f) {
				for (auto z = - length.getZ(); z < length.getZ(); z += 1.0f) {
					positions.push_back(Vector3d<float>(x, y, z));
					SPHParticle* particle = new SPHParticle(Vector3d<float>(x, y, z), 0.5f, 1000.0f, 1000.0f, 100.0f);
					sampleParticles.push_back(particle);
				}
			}
		}
	}
	//box.getMin
};

BulletRigid::~BulletRigid()
{
	clear();
}

void BulletRigid::clear()
{
	for (auto p : sampleParticles) {
		delete p;
	}
	sampleParticles.clear();
}

/*
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
*/

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
	btTransform transform;
	body->getMotionState()->getWorldTransform(transform);
	return BulletConverter::convert(transform.getRotation());
}

Surfels BulletRigid::toSurlfes(const float divideLength) const
{
	const auto& translate = getOrigin();
	const auto& rotation = getOrientation();

	Surfels surfels(positions);
	surfels.transform(translate, rotation);
	return surfels;
}

std::vector<SPHParticle*> BulletRigid::getSurfaceParticles()
{
	const auto& translate = getOrigin();
	const auto& rotation = getOrientation();
	std::vector<Vector3d<float>> result;
	const auto& matrix = rotation.toMatrix();
	for (int i = 0; i < positions.size(); ++i) {
		sampleParticles[i]->moveTo(Vector3d<float>(0.0f, 0.0f, 0.0f));
		sampleParticles[i]->rotate(matrix);
		sampleParticles[i]->moveTo(positions[i] + translate);
	}
	return sampleParticles;
}
