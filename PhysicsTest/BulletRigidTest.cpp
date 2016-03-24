#include "gtest/gtest.h"
#include "../Physics/BulletRigid.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(BulletRigidTest, TestGetMass)
{
	Box<float> box( Vector3d<float>(-0.5f, -0.5f, -0.5f), Vector3d<float>(0.5f, 0.5f, 0.5f));
	BulletRigid rigid(box, 1.0f);
	EXPECT_EQ(1.0f, rigid.getMass());
}

TEST(BulletRigidTest, TestToSurfels)
{
	Box<float> box(Vector3d<float>(-0.5f, -0.5f, -0.5f), Vector3d<float>(0.5f, 0.5f, 0.5f));
	BulletRigid rigid(box, 1.0f);
	rigid.toSurlfes(0.1f);
}