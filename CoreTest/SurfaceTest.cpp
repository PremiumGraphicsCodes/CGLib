#include "stdafx.h"
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

	EXPECT_EQ( p1, curve.get(0, 0) );
	EXPECT_EQ( p2, curve.get(0, 1) );
	EXPECT_EQ( p3, curve.get(1, 0) );
	EXPECT_EQ( p4, curve.get(1, 1));

	Surface surface(curve);
	EXPECT_EQ(12, surface.getEdges().size());
	EXPECT_EQ(4, surface.getNodes().size());
	EXPECT_EQ(4, surface.getFaces().size());

}

TEST(SurfaceTest, TestGetBoundingBox)
{
	Curve3d<float> curve(2, 2);

	Point3d<float> p1(Vector3d<float>(0, 0, 0));
	Point3d<float> p2(Vector3d<float>(0, 1, 0));
	Point3d<float> p3(Vector3d<float>(1, 0, 0));
	Point3d<float> p4(Vector3d<float>(1, 1, 0));

	curve.set(0, 0, p1);
	curve.set(0, 1, p2);
	curve.set(1, 0, p3);
	curve.set(1, 1, p4);

	Surface surface(curve);
	Box3d<float> expected(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 1, 0));
	Box3d<float> actual = surface.getBoundingBox();
	EXPECT_EQ( expected, actual);
}

TEST(SurfaceTest, TestGetBoundingSphere)
{
	Curve3d<float> curve(2, 2);

	Point3d<float> p1(Vector3d<float>(0, 0, 0));
	Point3d<float> p2(Vector3d<float>(0, 2, 0));
	Point3d<float> p3(Vector3d<float>(2, 0, 0));
	Point3d<float> p4(Vector3d<float>(2, 2, 0));

	curve.set(0, 0, p1);
	curve.set(0, 1, p2);
	curve.set(1, 0, p3);
	curve.set(1, 1, p4);

	Surface surface(curve);
	Sphere<float> expected(Vector3d<float>(1, 1, 0.0), std::sqrt(2));
	Sphere<float> actual = surface.getBoundingSphere();
	EXPECT_EQ(expected, actual);
}
