#include "gtest\gtest.h"
#include "../Math/Point3d.h"

using namespace Crystal::Math;

TEST(Point3dTest, TestLerp)
{
	const Point3d<float> p1(Vector3d<float>(0,0,0), Vector3d<float>(1,0,0));
	const Point3d<float> p2(Vector3d<float>(1,0,0), Vector3d<float>(0,1,0));
	const Point3d<float> expected(Vector3d<float>(0.5, 0, 0), Vector3d<float>(0.5, 0.5, 0));
	const auto& actual = p1.lerp(p2, 0.5);
	EXPECT_EQ(expected, actual);
}