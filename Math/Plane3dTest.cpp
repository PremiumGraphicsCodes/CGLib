#include "gtest/gtest.h"
#include "Plane3d.h"

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
