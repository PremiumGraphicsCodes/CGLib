#include "gtest/gtest.h"
#include "../Physics/BulletRigid.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(BulletRigidTest, TestGetMass)
{
	SPHConstant constant;
	Box<float> box( Vector3d<float>(-0.5f, -0.5f, -0.5f), Vector3d<float>(0.5f, 0.5f, 0.5f));
	BulletRigid rigid(box, &constant);
	EXPECT_FLOAT_EQ(1000.0f, rigid.getMass());
}
