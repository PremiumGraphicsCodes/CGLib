#include "gtest\gtest.h"
#include "../Core/Surface.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(SurfaceTest, Test)
{
	Curve3d<float> curve(2,2);

	Point3d<float> p1(Vector3d<float>(0, 0, 0));
	Point3d<float> p2(Vector3d<float>(0, 1, 0));
	Point3d<float> p3(Vector3d<float>(1, 0, 0));
	Point3d<float> p4(Vector3d<float>(1, 1, 0));

	curve.set(0, 0, p1);
	curve.set(0, 1, p2);
	curve.set(1, 0, p3);
	curve.set(1, 1, p4);

	Surface surface(curve);
	EXPECT_EQ(12, surface.getEdges().size());
	EXPECT_EQ(4, surface.getNodes().size());
	EXPECT_EQ(4, surface.getFaces().size());

}