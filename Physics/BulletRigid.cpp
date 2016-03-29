#include "BulletRigid.h"

#include "Bullet.h"
#include "BulletConverter.h"
#include "SPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

BulletRigid::BulletRigid(const Box<float>& box, SPHConstant* constant, bool isStatic)
{
	const auto mass = isStatic ? 0.0f : box.getVolume() * constant->getDensity();
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
		Box<float> box(-halfLength,halfLength);
		Surfels surfels(box, constant->getEffectLength() / 1.25f);
		localPositions = surfels.toPositions();
		for (auto pos : localPositions) {
			SPHParticle* particle = new SPHParticle(pos, constant->getEffectLength() / 1.25f * 0.5f, constant);
			sampleParticles.push_back(particle);
		}

	}
	localBox = Box<float>(-halfLength, halfLength);
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
		const auto& f = p->getForce(); // / p->getDensity(); /// p->getDensity();// / p->getDensity();
		const auto& diff = p->getPosition() - center;
		body->applyForce(BulletConverter::convert(f), BulletConverter::convert(diff));
	}
}

void BulletRigid::move(const Vector3d<float>& v)
{
	body->activate(true);
	body->translate(BulletConverter::convert(v) );// applyCentralForce(BulletConverter::convert(force));
}

void BulletRigid::addForce(const Vector3d<float>& f)
{
	body->applyCentralForce(BulletConverter::convert(f));
}