#include "gtest/gtest.h"
#include "../Physics/BulletRigid.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(BulletRigidTest, TestGetMass)
{
	Box<float> box;
	BulletRigid rigid(box, 1.0f);
	EXPECT_EQ(1.0f, rigid.getMass());
}

TEST(BulletRigidTest, TestToSurfels)
{
	Box<float> box;
	BulletRigid rigid(box, 1.0f);
	rigid.toSurlfes(0.1f);
}