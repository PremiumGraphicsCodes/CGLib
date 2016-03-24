#include "BulletRigid.h"

#include "Bullet.h"
#include "BulletConverter.h"
#include "SPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

BulletRigid::BulletRigid(const Box<float>& box, const float mass)
{
	const auto halfLength = box.getLength() * 0.5f;
	const auto origin = box.getCenter();
	auto shape = new btBoxShape(BulletConverter::convert(halfLength));
	btTransform transform;
	transform.setIdentity();
	transform.setOrigin( BulletConverter::convert(origin) );

	btVector3 inertia;
	shape->calculateLocalInertia(mass, inertia);

	btDefaultMotionState* motionState = new btDefaultMotionState(transform);
	btRigidBody::btRigidBodyConstructionInfo info(mass, motionState, shape, inertia);
	body = new btRigidBody(info);

	if (mass != 0.0f) {
		/*
		for (auto x = -halfLength.getX(); x <= halfLength.getX(); x += 1.0f) {
			for (auto y = -halfLength.getY(); y <= halfLength.getY(); y += 1.0f) {
				for (auto z = -halfLength.getZ(); z <= halfLength.getZ(); z += 1.0f) {
					const auto pos = Vector3d<float>(x, y, z);
					positions.push_back(pos);
					SPHParticle* particle = new SPHParticle(pos, 0.5f, 1000.0f, 1000.0f, 100.0f);
					sampleParticles.push_back(particle);
				}
			}
		}
		*/
		Box<float> box(-halfLength,halfLength);
		Surfels surfels(box, 1.0f);
		localPositions = surfels.toPositions();
		for (auto pos : localPositions) {
			SPHParticle* particle = new SPHParticle(pos, 0.5f, 1000.0f, 1000.0f, 100.0f);
			sampleParticles.push_back(particle);
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

Matrix4d<float> BulletRigid::getTransformMatrix() const
{
	btTransform transform;
	body->getMotionState()->getWorldTransform(transform);
	return BulletConverter::convert(transform);
}


Surfels BulletRigid::toSurlfes(const float divideLength) const
{
	const auto& translate = getOrigin();
	const auto& rotation = getOrientation();

	Surfels surfels(localPositions);
	surfels.transform(translate, rotation);
	return surfels;
}

void BulletRigid::transform()
{
	const auto& translate = getOrigin();
	const auto& rotation = getOrientation();
	std::vector<Vector3d<float>> result;
	const auto& matrix = rotation.toMatrix();
	for (int i = 0; i < localPositions.size(); ++i) {
		sampleParticles[i]->moveTo(localPositions[i]);
		sampleParticles[i]->rotate(matrix);
		sampleParticles[i]->move(translate);
	}

}


std::vector<SPHParticle*> BulletRigid::getSurfaceParticles()
{
	return sampleParticles;
}

void BulletRigid::solveBoundary()
{
	const auto& center = BulletConverter::convert( body->getCenterOfMassPosition() );
	for (const auto p : sampleParticles) {
		const auto& f = p->getForce();// / p->getDensity();// / p->getDensity();
		const auto& diff = p->getPosition() - center;
		body->applyForce(BulletConverter::convert(f), BulletConverter::convert(diff));
	}
}
