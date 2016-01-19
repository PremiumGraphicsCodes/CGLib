#include "gtest/gtest.h"

#include "../Math/Triangle.h"

using namespace Crystal::Math;

template<class T>
class TriangleTest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE(TriangleTest, TestTypes);


TYPED_TEST(TriangleTest, TestGet)
{
	using T = TypeParam;
	EXPECT_EQ(Vector3d<T>(0, 0, 0), Triangle<T>().getv0());
	EXPECT_EQ(Vector3d<T>(1, 0, 0), Triangle<T>().getv1());
	EXPECT_EQ(Vector3d<T>(0, 1, 0), Triangle<T>().getv2());
}

TYPED_TEST(TriangleTest, TestGetArea)
{
	using T = TypeParam;
	EXPECT_EQ( 0.5, Triangle<T>().getArea() );
}

/*
TYPED_TEST(TriangleTest, TestIsShrinked)
{
	using T = TypeParam;
	EXPECT_FALSE(Triangle<T>().isShrinked() );
}
*/

TYPED_TEST(TriangleTest, TestGetNormal)
{
	using T = TypeParam;
	EXPECT_EQ(Vector3d<T>::UnitZ(), Triangle<T>::UnitXY().getNormal());
	EXPECT_EQ(Vector3d<T>::UnitY(), Triangle<T>::UnitXZ().getNormal());
	EXPECT_EQ(Vector3d<T>::UnitX(), Triangle<T>::UnitYZ().getNormal());

	const auto actual = Triangle<T>(
		Vector3d<T>(0,0,0),
		Vector3d<T>(1,0,0),
		Vector3d<T>(1,0,1)
		).getNormal();
	EXPECT_EQ(Vector3d<T>(0, -1, 0), actual);
}

TYPED_TEST(TriangleTest, TestIsCCW)
{
	using T = TypeParam;
	EXPECT_TRUE( Triangle<T>().isCCW() );
}
