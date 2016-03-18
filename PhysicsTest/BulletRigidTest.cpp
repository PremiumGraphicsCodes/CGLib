#include "gtest/gtest.h"
#include "../Physics/BulletRigid.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(BulletRigidTest, TestGetMass)
{
	Box<float> box;

	BulletRigid rigid(Vector3d<float>(1.0f, 1.0f, 1.0f), Vector3d<float>(1.0f, 1.0f, 1.0f), 1.0f);
	EXPECT_EQ(1.0f, rigid.getMass());
}

TEST(BulletRigidTest, TestToSurfels)
{
	Box<float> box;
	BulletRigid rigid(Vector3d<float>(1.0f, 1.0f, 1.0f), Vector3d<float>(1.0f, 1.0f, 1.0f), 1.0f);
	rigid.toSurlfes(0.1f);
}