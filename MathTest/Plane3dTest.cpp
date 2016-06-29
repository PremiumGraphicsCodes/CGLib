#include "gtest/gtest.h"
#include "../Math/Plane3d.h"
#include "../Math/Line3d.h"

using namespace Crystal::Math;

TEST(Plane3dTest, TestGetNormal)
{
	EXPECT_EQ( Vector3d<float>(0,0,1), Plane3d<float>::XYPlane().getNormal() );
	EXPECT_EQ( Vector3d<float>(1,0,0), Plane3d<float>::YZPlane().getNormal() );
	EXPECT_EQ( Vector3d<float>(0,1,0), Plane3d<float>::ZXPlane().getNormal() );
}

TEST(Plane3dTest, TestGetDistance)
{
	EXPECT_EQ(4, Plane3d<float>::XYPlane().getSignedDistance( Vector3d<float>(2, 3, 4)) );
	EXPECT_EQ(-4, Plane3d<float>::XYPlane().getSignedDistance( Vector3d<float>(-2, -3, -4)));
	EXPECT_EQ(2, Plane3d<float>::YZPlane().getSignedDistance(Vector3d<float>(2, 3, 2)));
	EXPECT_EQ(-2, Plane3d<float>::YZPlane().getSignedDistance(Vector3d<float>(-2, -3, -2)));

}

TEST(Plane3dTest, TestHasIntersection)
{
	const auto& planexz = Plane3d<float>::ZXPlane();// (Vector3d<float>(0, 0, 0), Vector3d<float>(2, 0, 0), Vector3d<float>(0, 0, 2));

	const Line3d<float> line1(Vector3d<float>(1, 1, 1), Vector3d<float>(2, 2, 2));
	const Line3d<float> xyzcorss(Vector3d<float>(-1, -1, -1), Vector3d<float>(2, 2, 2));
	const Line3d<float> xcross(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0));
	const Line3d<float> ycross(Vector3d<float>(0, -1, 0), Vector3d<float>(0, 1, 0));
	const Line3d<float> zcross(Vector3d<float>(0, 0, -1), Vector3d<float>(0, 0, 1));

	{
		EXPECT_FALSE(planexz.hasIntersection(line1));
		EXPECT_TRUE( planexz.hasIntersection(xyzcorss));
		EXPECT_FALSE(planexz.hasIntersection(xcross));
		EXPECT_TRUE( planexz.hasIntersection(ycross));
		EXPECT_FALSE( planexz.hasIntersection(zcross));

	}
	{
		const auto& plane = Plane3d<float>::YZPlane();
		EXPECT_FALSE(plane.hasIntersection(line1));
		EXPECT_TRUE(plane.hasIntersection(xyzcorss));
		EXPECT_TRUE(plane.hasIntersection(xcross));
		EXPECT_FALSE(plane.hasIntersection(ycross));
		EXPECT_FALSE(plane.hasIntersection(zcross));

	}
}