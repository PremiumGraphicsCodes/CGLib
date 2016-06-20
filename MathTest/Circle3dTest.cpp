#include "gtest\gtest.h"
#include "../Math/Circle3d.h"

using namespace Crystal::Math;

TEST(Circle3dTest, Test)
{
	Quaternion<float> q(Vector3d<float>(1, 0, 0), 0);
	Circle3d<float> circle(0.5, Vector3d<float>(0,0,0),q);
	EXPECT_EQ( Vector3d<float>(0.5,0,0), circle.getPosition(Angle<float>::Zero()));
	EXPECT_EQ(Vector3d<float>(-0.5, 0, 0), circle.getPosition(Angle<float>::PI()));

}