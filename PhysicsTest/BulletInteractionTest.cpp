#include "gtest/gtest.h"
#include "../Physics/BulletInteraction.h"

#include "../Physics/PhysicsWorld.h"
#include "../ThirdParty/bullet/src/btBulletDynamicsCommon.h"

using namespace Crystal::Physics;

TEST(BulletInteractionTest, Test)
{
	ParticleWorld particleWorld;

	BulletWorld bulletWorld;

	BulletInteraction interaction(&particleWorld, &bulletWorld);
	interaction.simulate(1.0f);
}