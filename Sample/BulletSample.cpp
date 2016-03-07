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

BulletSample::~BulletSample()
{
	cleanup();
}

void BulletSample::setup()
{


	world.setGravity(btVector3(0, -9.8, 0));

	auto colShape = new btSphereShape(btScalar(1.));
	
	btTransform startTransform;
	startTransform.setIdentity();

	btScalar mass(1.0f);
	bool isDynamic = (mass != 0.0f);

	btVector3 localInertia(0, 0, 0);
	if (isDynamic) {
		colShape->calculateLocalInertia(mass, localInertia);
	}

	startTransform.setOrigin(btVector3(0, 0, 0));

	auto state = new btDefaultMotionState(startTransform);
	btRigidBody::btRigidBodyConstructionInfo rbInfo
			(
				mass,
				state,
				colShape,
				localInertia
				);
	rigid = new btRigidBody(rbInfo);
	world.addRigidBody(rigid);
}

void BulletSample::demonstrate()
{
	glEnable(GL_DEPTH_TEST);
	world.stepSimulation(1.0f/ 60.0f / 1000.0f, 10);

	PerspectiveCamera<float> camera;
	camera.moveTo(Vector3d<float>(0.0, 0.0, -5.0));
	camera.setCameraXY();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		LegacyRenderer renderer;
		PointBuffer buffer;
		ColorRGBA<float> color(1.0, 1.0, 1.0, 1.0);
		const auto x = rigid->getWorldTransform().getOrigin().getX();
		const auto y = rigid->getWorldTransform().getOrigin().getY();
		const auto z = rigid->getWorldTransform().getOrigin().getZ();
		Point point( Vector3d<float>(x,y,z), ColorRGBA<float>(1.0, 0.0, 0.0, 1.0), 10.0f);
		buffer.add(point);
		renderer.render(camera, buffer);
}

void BulletSample::cleanup()
{

}

//#endif