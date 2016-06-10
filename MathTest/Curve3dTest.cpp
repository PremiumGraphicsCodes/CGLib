#include "gtest\gtest.h"

#include "../Math/Curve3d.h"

using namespace Crystal::Math;

TEST(Curve3dTest, TestGetSet)
{
	Curve3d<float> curve(1, 2);
	Point3d<float> point(Vector3d<float>(1, 2, 3));
	curve.set(0, 1, point);
	const auto& actual = curve.get(0, 1);
	EXPECT_EQ(Vector3d<float>(1, 2, 3), actual.getPosition());
}

TEST(Curve3dTest, TestMove)
{
	Curve3d<float> curve(2, 2);
	Point3d<float> point(Vector3d<float>(1,2,3));
	curve.set(0, 0, point);
	curve.move(Vector3d<float>(1, 1, 1));
	const auto& actual = curve.get(0, 0);
	EXPECT_EQ(Vector3d<float>(2, 3, 4), actual.getPosition());
}