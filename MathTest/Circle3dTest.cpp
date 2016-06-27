#include "gtest\gtest.h"
#include "../Math/Circle3d.h"
#include "../Math/PolyLine3d.h"

using namespace Crystal::Math;

TEST(Circle3dTest, Test)
{
	Quaternion<float> q(Vector3d<float>(1, 0, 0), 0);
	Circle3d<float> circle(0.5, Vector3d<float>(0,0,0),q);
	EXPECT_EQ( Vector3d<float>(0.5,0,0), circle.getPosition(Angle<float>::Zero()));
	EXPECT_EQ(Vector3d<float>(-0.5, 0, 0), circle.getPosition(Angle<float>::PI()));
}

TEST(Circle3dTest, TestToPolyline)
{
	Quaternion<float> q(Vector3d<float>(1, 0, 0), 0);
	Circle3d<float> circle(0.5, Vector3d<float>(0, 0, 0), q);
	Polyline3d<float> expected;
	expected.add(Vector3d<float>(0.5, 0, 0));
	expected.add(Vector3d<float>(-0.5, 0, 0));
	EXPECT_EQ( expected, circle.toPolyline(2) );
}