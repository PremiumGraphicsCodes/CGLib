#include "BulletWorld.h"
#include "BulletRigid.h"
#include "BulletConverter.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

BulletWorld::BulletWorld():
	dispatcher(&collisionConfig)
{
	world = new btDiscreteDynamicsWorld(&dispatcher, &overlappingPairCache, &solver, &collisionConfig);
}

void BulletWorld::add(BulletRigid* rigid)
{
	world->addRigidBody(rigid->getBody());
	rigids.push_back(rigid);
}

void BulletWorld::setExternalForce(const Vector3d<float>& f)
{
	world->setGravity(BulletConverter::convert(f));
}

void BulletWorld::simulate(const float timeStep)
{
	world->stepSimulation(timeStep, 10);
}

void BulletWorld::setBoundary(const Box<float>& box)
{
	{
		btStaticPlaneShape* shape = new btStaticPlaneShape(btVector3(0.0f, 1.0f, 0.0f), box.getMinY());
		btDefaultMotionState* state = new btDefaultMotionState();
		btRigidBody::btRigidBodyConstructionInfo plain_body_ci(0.0f, state, shape);
		btRigidBody* body = new btRigidBody(plain_body_ci);
		world->addRigidBody(body);
	}

	{
		btStaticPlaneShape* shape = new btStaticPlaneShape(btVector3(1.0f, 0.0f, 0.0f), box.getMinX());
		btDefaultMotionState* state = new btDefaultMotionState();
		btRigidBody::btRigidBodyConstructionInfo plain_body_ci(0.0f, state, shape);
		btRigidBody* body = new btRigidBody(plain_body_ci);
		world->addRigidBody(body);
	}

	{
		btCollisionShape* shape = new btStaticPlaneShape(btVector3(0.0f, 0.0f, 1.0f), box.getMinZ());
		btDefaultMotionState* state = new btDefaultMotionState();
		btRigidBody::btRigidBodyConstructionInfo plain_body_ci(0.0f, state, shape);
		btRigidBody* body = new btRigidBody(plain_body_ci);
		world->addRigidBody(body);
	}
}
