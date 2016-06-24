#include "gtest\gtest.h"

#include "../Math/TriangleCurve3d.h"

using namespace Crystal::Math;

TEST(TriangleCurve3dTest, TestGetSet)
{
	TriangleCurve3d<float> curve(2);
	Point3d<float> point00(Vector3d<float>(0, 0, 0));
	Point3d<float> point10(Vector3d<float>(1, 0, 0));
	Point3d<float> point11(Vector3d<float>(1, 1, 0));

	curve.set(0, 0, point00);
	curve.set(1, 0, point10);
	curve.set(1, 1, point11);
	EXPECT_EQ(Vector3d<float>(0, 0, 0), curve.get(0,0).getPosition());
	EXPECT_EQ(Vector3d<float>(1, 0, 0), curve.get(1, 0).getPosition());
	EXPECT_EQ(Vector3d<float>(1, 1, 0), curve.get(1, 1).getPosition());

}
