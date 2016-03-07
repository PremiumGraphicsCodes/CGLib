//#ifdef __CRYSTAL_USE_BULLET_H__


#include "BulletSample.h"

#include "../Graphics/PointBuffer.h"
#include "../Graphics/PerspectiveCamera.h"

#include "../Shader/LegacyRenderer.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;

BulletSample::BulletSample() :
	dispatcher(&collisionConfig),
	world(&dispatcher, &overlappingPairCache, &solver, &collisionConfig)
{
}

void BulletSample::setup()
{
	world.setGravity(btVector3(0, -9.8, 0));

	{
		auto shape = new btSphereShape(btScalar(1.0f));
		btVector3 localInertia(0, 0, 0);
		btScalar mass(1.0f);
		shape->calculateLocalInertia(mass, localInertia);

		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setOrigin(btVector3(0, 0, 0));

		auto state = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, state, shape, localInertia);
		rigid = new btRigidBody(rbInfo);
		world.addRigidBody(rigid);
	}

	{
		auto shape = new btSphereShape(btScalar(1.0f));
		btVector3 localInertia(0, 0, 0);
		btScalar mass(10.0f);
		shape->calculateLocalInertia(mass, localInertia);

		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setOrigin(btVector3(0, 2, 0));

		auto state = new btDefaultMotionState(startTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, state, shape, localInertia);
		rigid2 = new btRigidBody(rbInfo);
		world.addRigidBody(rigid2);
	}


	{
		btCollisionShape* groundShape = new btBoxShape(btVector3(btScalar(50.), btScalar(50.), btScalar(50.)));
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(0, -55.0f, 0));
		btScalar groundMass(0.0f);
		btVector3 localInertia(0, 0, 0);
		btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(groundMass, myMotionState, groundShape, localInertia);
		btRigidBody* body = new btRigidBody(rbInfo);
		world.addRigidBody(body);
	}
}

void BulletSample::demonstrate()
{
	glEnable(GL_DEPTH_TEST);
	world.stepSimulation(1.0f/ 60.0f / 100.0f, 10);

	PerspectiveCamera<float> camera;
	camera.moveTo(Vector3d<float>(0.0, 0.0, -5.0));
	camera.setCameraXY();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	LegacyRenderer renderer;
	PointBuffer buffer;
	ColorRGBA<float> color(1.0, 1.0, 1.0, 1.0);
	{
		const auto x = rigid->getWorldTransform().getOrigin().getX();
		const auto y = rigid->getWorldTransform().getOrigin().getY();
		const auto z = rigid->getWorldTransform().getOrigin().getZ();
		Point point(Vector3d<float>(x, y, z), ColorRGBA<float>(1.0, 0.0, 0.0, 1.0), 10.0f);
		buffer.add(point);
	}
	{
		const auto x = rigid2->getWorldTransform().getOrigin().getX();
		const auto y = rigid2->getWorldTransform().getOrigin().getY();
		const auto z = rigid2->getWorldTransform().getOrigin().getZ();
		Point point(Vector3d<float>(x, y, z), ColorRGBA<float>(1.0, 0.0, 0.0, 1.0), 10.0f);
		buffer.add(point);
	}

	renderer.render(camera, buffer);
}
