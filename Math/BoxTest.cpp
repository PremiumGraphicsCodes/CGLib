#include "gtest/gtest.h"
 
#include "../Math/Box.h"

using namespace Crystal::Math;
 
template<class T>
class BoxTest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE(BoxTest, TestTypes);

TYPED_TEST( BoxTest, TestGetMin )
{
	using T = TypeParam;
	EXPECT_EQ( Vector3d<T>(0, 0, 0), Box<T>().getMin() );
	EXPECT_EQ( Vector3d<T>(1, 2, 3), Box<T>( Vector3d<T>(1, 2, 3), Vector3d<T>(4, 5, 6) ).getMin());
}

TYPED_TEST(BoxTest, TestGetMax)
{
	using T = TypeParam;
	EXPECT_EQ(Vector3d<T>(1, 1, 1), Box<T>().getMax());
	EXPECT_EQ(Vector3d<T>(4, 5, 6), Box<T>(Vector3d<T>(1, 2, 3), Vector3d<T>(4, 5, 6)).getMax());
}

TYPED_TEST( BoxTest, TestGetVolume )
{
	using T = TypeParam;
	EXPECT_TRUE(Tolerance<T>::isEqualLoosely(6, Box<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 2, 3)).getVolume()));
}

TYPED_TEST( BoxTest, TestGetLength )
{
	using T = TypeParam;
	EXPECT_EQ( Vector3d<T>(0.0, 1.0, 2.0), Box<T>(Vector3d<T>(1.0f, 1.0f, 1.0f), Vector3d<T>(1.0f, 2.0f, 3.0f)).getLength());
}

TYPED_TEST( BoxTest, TestOuterOffset )
{
	using T = TypeParam;
	EXPECT_EQ(Box<T>(Vector3d<T>(-1.0f, -1.0f, -1.0f), Vector3d<T>(2.0f, 2.0f, 2.0f)), Box<T>().getOuterOffset(1.0f));
}

TYPED_TEST( BoxTest, TestIsShrinked )
{
	using T = TypeParam;

	EXPECT_TRUE(Box<T>(Vector3d<T>(0.0f, 0.0f, 0.0f), Vector3d<T>(0.0f, 0.0f, 0.0f)).isShirinked());
	EXPECT_FALSE(Box<T>(Vector3d<T>(0.0f, 0.0, 0.0f), Vector3d<T>(1.0f, 1.0f, 1.0f)).isShirinked());
}

TYPED_TEST( BoxTest, TestIsValid )
{
	using T = TypeParam;

	EXPECT_TRUE(Box<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(0, 0, 0)).isValid());
	EXPECT_TRUE(Box<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1)).isValid());
}

TYPED_TEST(BoxTest, TestHasIntersection)
{
	using T = TypeParam;

	EXPECT_FALSE(Box<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1)).hasIntersection(  Box<T>( Vector3d<T>(2, 2, 2), Vector3d<T>(4, 4, 4) ) ));
}

TYPED_TEST(BoxTest, TestGetOverlapped)
{
	using T = TypeParam;

	const Box<T> b1(Vector3d<T>(0, 0, 0), Vector3d<T>(2, 2, 2));
	const Box<T> b2(Vector3d<T>(1, 1, 1), Vector3d<T>(5, 5, 5));
	const Box<T> expected(Vector3d<T>(1,1,1), Vector3d<T>(2,2,2));
	const auto actual = b1.getOverlapped(b2);
	EXPECT_EQ(expected, actual);
}