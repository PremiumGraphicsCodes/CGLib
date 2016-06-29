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
	const auto& planezx = Plane3d<float>::ZXPlane();
	const auto& planeyz = Plane3d<float>::YZPlane();
	const auto& planexy = Plane3d<float>::XYPlane();

	const Line3d<float> line1(Vector3d<float>(1, 1, 1), Vector3d<float>(2, 2, 2));
	const Line3d<float> xyzcross(Vector3d<float>(-1, -1, -1), Vector3d<float>(2, 2, 2));
	const Line3d<float> xcross(Vector3d<float>(-1, 1, 1), Vector3d<float>(1, 1, 1));
	const Line3d<float> ycross(Vector3d<float>(1, -1, 1), Vector3d<float>(1, 1, 1));
	const Line3d<float> zcross(Vector3d<float>(1, 1, -1), Vector3d<float>(1, 1, 1));

	EXPECT_FALSE(planezx.hasIntersection(line1));
	EXPECT_FALSE(planezx.hasIntersection(xcross));
	EXPECT_TRUE( planezx.hasIntersection(ycross));
	EXPECT_FALSE(planezx.hasIntersection(zcross));
	EXPECT_TRUE( planezx.hasIntersection(xyzcross));

	EXPECT_FALSE(planeyz.hasIntersection(line1));
	EXPECT_TRUE( planeyz.hasIntersection(xcross));
	EXPECT_FALSE(planeyz.hasIntersection(ycross));
	EXPECT_FALSE(planeyz.hasIntersection(zcross));
	EXPECT_TRUE( planeyz.hasIntersection(xyzcross));

	EXPECT_FALSE(planexy.hasIntersection(line1));
	EXPECT_FALSE(planexy.hasIntersection(xcross));
	EXPECT_FALSE(planexy.hasIntersection(ycross));
	EXPECT_TRUE( planexy.hasIntersection(zcross));
	EXPECT_TRUE(planeyz.hasIntersection(xyzcross));

}

TEST(Plane3dTest, TestGetIntersection)
{
	const auto& planezx = Plane3d<float>::ZXPlane();// (Vector3d<float>(0, 0, 0), Vector3d<float>(2, 0, 0), Vector3d<float>(0, 0, 2));
	const auto& planeyz = Plane3d<float>::YZPlane();
	const auto& planexy = Plane3d<float>::XYPlane();

	const Line3d<float> xcross(Vector3d<float>(-1, 1, 1), Vector3d<float>(1, 1, 1));
	const Line3d<float> ycross(Vector3d<float>(1, -1, 1), Vector3d<float>(1, 1, 1));
	const Line3d<float> zcross(Vector3d<float>(1, 1, -1), Vector3d<float>(1, 1, 1));
	const Line3d<float> xyzcross(Vector3d<float>(-1, -1, -1), Vector3d<float>(2, 2, 2));


	EXPECT_EQ( Vector3d<float>(0,0,0), planezx.getIntersection(xyzcross));
	EXPECT_EQ( Vector3d<float>(1,0,1), planezx.getIntersection(ycross));
	EXPECT_EQ( Vector3d<float>(0,1,1), planeyz.getIntersection(xcross));
	EXPECT_EQ( Vector3d<float>(0,0,0), planeyz.getIntersection(xyzcross));
	EXPECT_EQ( Vector3d<float>(1,1,0), planexy.getIntersection(zcross));
	EXPECT_EQ( Vector3d<float>(0,0,0), planexy.getIntersection(xyzcross));

	//EXPECT_FALSE(planexz.hasIntersection(zcross));
}