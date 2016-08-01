#include "gtest\gtest.h"
#include "../Math/Circle3d.h"
#include "../Math/PolyLine3d.h"

using namespace Crystal::Math;

template<class T>
class Circle3dTest : public testing::Test {};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE(Circle3dTest, TestTypes);

TYPED_TEST(Circle3dTest, Test)
{
	using T = TypeParam;
	Quaternion<T> q(Vector3d<T>(1, 0, 0), 0);
	Circle3d<T> circle(0.5, Vector3d<T>(0,0,0),q);
	EXPECT_EQ(Vector3d<T>(0.5,0,0), circle.getPosition(Angle<T>::Zero()));
	EXPECT_EQ(Vector3d<T>(-0.5, 0, 0), circle.getPosition(Angle<T>::PI()));
}

TYPED_TEST(Circle3dTest, TestToPolyline)
{
	using T = TypeParam;
	Quaternion<T> q(Vector3d<T>(1, 0, 0), 0);
	Circle3d<T> circle(0.5, Vector3d<T>(0, 0, 0), q);
	Polyline3d<T> expected;
	expected.add(Vector3d<T>(0.5, 0, 0));
	expected.add(Vector3d<T>(-0.5, 0, 0));
	EXPECT_EQ( expected, circle.toPolyline(2) );
}