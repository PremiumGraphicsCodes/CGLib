#include "BulletWorld.h"

using namespace Crystal::Physics;

BulletWorld::BulletWorld():
	dispatcher(&collisionConfig)
{
	world = new btDiscreteDynamicsWorld(&dispatcher, &overlappingPairCache, &solver, &collisionConfig);
}