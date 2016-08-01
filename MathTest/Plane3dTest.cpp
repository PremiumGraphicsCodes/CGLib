#include "gtest/gtest.h"
#include "../Math/Plane3d.h"
#include "../Math/Line3d.h"

using namespace Crystal::Math;

template<class T>
class Plane3dTest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE(Plane3dTest, TestTypes);


TYPED_TEST(Plane3dTest, TestGetNormal)
{
	using T = TypeParam;
	EXPECT_EQ( Vector3d<T>(0,0,1), Plane3d<T>::XYPlane().getNormal() );
	EXPECT_EQ( Vector3d<T>(1,0,0), Plane3d<T>::YZPlane().getNormal() );
	EXPECT_EQ( Vector3d<T>(0,1,0), Plane3d<T>::ZXPlane().getNormal() );
}

TYPED_TEST(Plane3dTest, TestGetDistance)
{
	using T = TypeParam;
	EXPECT_EQ( 4, Plane3d<T>::XYPlane().getSignedDistance( Vector3d<T>(2, 3, 4)) );
	EXPECT_EQ(-4, Plane3d<T>::XYPlane().getSignedDistance( Vector3d<T>(-2, -3, -4)));
	EXPECT_EQ( 2, Plane3d<T>::YZPlane().getSignedDistance( Vector3d<T>(2, 3, 2)));
	EXPECT_EQ(-2, Plane3d<T>::YZPlane().getSignedDistance( Vector3d<T>(-2, -3, -2)));
}

TYPED_TEST(Plane3dTest, TestGetPosition)
{
	using T = TypeParam;
	const Plane3d<T> xy(Vector3d<T>(0,0,0), Vector3d<T>(1,0,0), Vector3d<T>(0,1,0));
	EXPECT_EQ(Vector3d<T>(0,0,0), xy.getPosition(Param<T>(0), Param<T>(0)));
	EXPECT_EQ(Vector3d<T>(1,0,0), xy.getPosition(Param<T>(1), Param<T>(0)));
	EXPECT_EQ(Vector3d<T>(1,1,0), xy.getPosition(Param<T>(1), Param<T>(1)));
}

TYPED_TEST(Plane3dTest, TestHasIntersection)
{
	using T = TypeParam;
	const auto& planezx = Plane3d<T>::ZXPlane();
	const auto& planeyz = Plane3d<T>::YZPlane();
	const auto& planexy = Plane3d<T>::XYPlane();

	const Line3d<T> line1(Vector3d<T>(1, 1, 1), Vector3d<T>(2, 2, 2));
	const Line3d<T> xyzcross(Vector3d<T>(-1, -1, -1), Vector3d<T>(2, 2, 2));
	const Line3d<T> xcross(Vector3d<T>(-1, 1, 1), Vector3d<T>(1, 1, 1));
	const Line3d<T> ycross(Vector3d<T>(1, -1, 1), Vector3d<T>(1, 1, 1));
	const Line3d<T> zcross(Vector3d<T>(1, 1, -1), Vector3d<T>(1, 1, 1));

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
	EXPECT_TRUE( planeyz.hasIntersection(xyzcross));

}

TYPED_TEST(Plane3dTest, TestGetIntersection)
{
	using T = TypeParam;
	const auto& planezx = Plane3d<T>::ZXPlane();
	const auto& planeyz = Plane3d<T>::YZPlane();
	const auto& planexy = Plane3d<T>::XYPlane();

	const Line3d<T> xcross(Vector3d<T>(-1, 1, 1), Vector3d<T>(1, 1, 1));
	const Line3d<T> ycross(Vector3d<T>(1, -1, 1), Vector3d<T>(1, 1, 1));
	const Line3d<T> zcross(Vector3d<T>(1, 1, -1), Vector3d<T>(1, 1, 1));
	const Line3d<T> xyzcross(Vector3d<T>(-1, -1, -1), Vector3d<T>(2, 2, 2));

	EXPECT_EQ( Vector3d<T>(0,0,0), planezx.getIntersection(xyzcross));
	EXPECT_EQ( Vector3d<T>(1,0,1), planezx.getIntersection(ycross));
	EXPECT_EQ( Vector3d<T>(0,1,1), planeyz.getIntersection(xcross));
	EXPECT_EQ( Vector3d<T>(0,0,0), planeyz.getIntersection(xyzcross));
	EXPECT_EQ( Vector3d<T>(1,1,0), planexy.getIntersection(zcross));
	EXPECT_EQ( Vector3d<T>(0,0,0), planexy.getIntersection(xyzcross));
}