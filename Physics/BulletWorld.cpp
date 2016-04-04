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

void BulletWorld::setBoundary(const Box3d<float>& box)
{
	btBoxShape* worldBoxShape = new btBoxShape( BulletConverter::convert( box.getLength() * 0.5 ));

	///create 6 planes/half spaces
	for (int i = 0; i < 6; i++)
	{
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(BulletConverter::convert( box.getCenter()) );
		btVector4 planeEq;
		worldBoxShape->getPlaneEquation(planeEq, i);

		btCollisionShape* shape = new btStaticPlaneShape(-planeEq, planeEq[3]);
		btDefaultMotionState* state = new btDefaultMotionState(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo plain_body_ci(0.0f, state, shape);
		btRigidBody* body = new btRigidBody(plain_body_ci);
		world->addRigidBody(body);
	}
	/*
	{
		btStaticPlaneShape* shape = new btBoxShape(BulletConverter::convert(box));
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
	*/
}
