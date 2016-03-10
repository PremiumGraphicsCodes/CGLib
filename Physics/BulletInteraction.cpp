#include "BulletInteraction.h"

//#include "../ThirdParty/bullet/src/btBulletCollisionCommon.h"
#include "../ThirdParty/bullet/src/btBulletDynamicsCommon.h"
#include "PhysicsWorld.h"

//using namespace Crystal::Math;
using namespace Crystal::Physics;

BulletInteraction::BulletInteraction(ParticleWorld* particleWorld, btDiscreteDynamicsWorld* bulletWorld) :
	particleWorld( particleWorld ),
	bulletWorld( bulletWorld )
{
}

void BulletInteraction::forwardTime(const float timeStep)
{
	particleWorld->simulate(1.25f, timeStep);
	bulletWorld->stepSimulation(timeStep, 10);
}
