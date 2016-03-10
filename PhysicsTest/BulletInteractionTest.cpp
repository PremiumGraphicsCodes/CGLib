#include "gtest/gtest.h"
#include "../Physics/BulletInteraction.h"

#include "../Physics/PhysicsWorld.h"
#include "../ThirdParty/bullet/src/btBulletDynamicsCommon.h"

using namespace Crystal::Physics;

TEST(BulletInteractionTest, Test)
{
	ParticleWorld particleWorld;

	btDefaultCollisionConfiguration collisionConfig;
	btCollisionDispatcher dispatcher(&collisionConfig);
	btDbvtBroadphase overlappingPairCache;
	btSequentialImpulseConstraintSolver solver;
	btDiscreteDynamicsWorld bulletWorld(&dispatcher, &overlappingPairCache, &solver, &collisionConfig);

	BulletInteraction interaction(&particleWorld, &bulletWorld);
	interaction.forwardTime(1.0f);
}