#include "gtest/gtest.h"
 
#include "../Math/Box3d.h"

using namespace Crystal::Math;
 
template<class T>
class Box3dTest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE(Box3dTest, TestTypes);

TYPED_TEST( Box3dTest, TestGetMin )
{
	using T = TypeParam;
	EXPECT_EQ( Vector3d<T>(0, 0, 0), Box3d<T>().getMin() );
	EXPECT_EQ( Vector3d<T>(1, 2, 3), Box3d<T>( Vector3d<T>(1, 2, 3), Vector3d<T>(4, 5, 6) ).getMin());
}

TYPED_TEST(Box3dTest, TestGetMax)
{
	using T = TypeParam;
	EXPECT_EQ(Vector3d<T>(1, 1, 1), Box3d<T>().getMax());
	EXPECT_EQ(Vector3d<T>(4, 5, 6), Box3d<T>(Vector3d<T>(1, 2, 3), Vector3d<T>(4, 5, 6)).getMax());
}

TYPED_TEST( Box3dTest, TestGetVolume )
{
	using T = TypeParam;
	EXPECT_TRUE(Tolerance<T>::isEqualLoosely(6, Box3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 2, 3)).getVolume()));
}

TYPED_TEST( Box3dTest, TestGetLength )
{
	using T = TypeParam;
	EXPECT_EQ( Vector3d<T>(0.0, 1.0, 2.0), Box3d<T>(Vector3d<T>(1.0f, 1.0f, 1.0f), Vector3d<T>(1.0f, 2.0f, 3.0f)).getLength());
}

TYPED_TEST( Box3dTest, TestOuterOffset )
{
	using T = TypeParam;
	EXPECT_EQ(Box3d<T>(Vector3d<T>(-1.0f, -1.0f, -1.0f), Vector3d<T>(2.0f, 2.0f, 2.0f)), Box3d<T>().getOuterOffset(1.0f));
}

TYPED_TEST( Box3dTest, TestIsShrinked )
{
	using T = TypeParam;

	EXPECT_TRUE(Box3d<T>(Vector3d<T>(0.0f, 0.0f, 0.0f), Vector3d<T>(0.0f, 0.0f, 0.0f)).isShirinked());
	EXPECT_FALSE(Box3d<T>(Vector3d<T>(0.0f, 0.0, 0.0f), Vector3d<T>(1.0f, 1.0f, 1.0f)).isShirinked());
}

TYPED_TEST( Box3dTest, TestIsValid )
{
	using T = TypeParam;

	EXPECT_TRUE(Box3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(0, 0, 0)).isValid());
	EXPECT_TRUE(Box3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1)).isValid());
}

TYPED_TEST(Box3dTest, TestHasIntersection)
{
	using T = TypeParam;

	EXPECT_FALSE(Box3d<T>(Vector3d<T>(0, 0, 0), Vector3d<T>(1, 1, 1)).hasIntersection(  Box3d<T>( Vector3d<T>(2, 2, 2), Vector3d<T>(4, 4, 4) ) ));
}

TYPED_TEST(Box3dTest, TestGetOverlapped)
{
	using T = TypeParam;

	const Box3d<T> b1(Vector3d<T>(0, 0, 0), Vector3d<T>(2, 2, 2));
	const Box3d<T> b2(Vector3d<T>(1, 1, 1), Vector3d<T>(5, 5, 5));
	const Box3d<T> expected(Vector3d<T>(1,1,1), Vector3d<T>(2,2,2));
	const auto actual = b1.getOverlapped(b2);
	EXPECT_EQ(expected, actual);
}

TYPED_TEST(Box3dTest, TestAdd)
{
	using T = TypeParam;

	Box3d<T> b1(Vector3d<T>(0, 0, 0), Vector3d<T>(2, 2, 2));
	const Box3d<T> b2(Vector3d<T>(-1, 1, 1), Vector3d<T>(3, 3, 3));
	b1.add(b2);
	const Box3d<T> expected(Vector3d<T>(-1, 0, 0), Vector3d<T>(3, 3, 3));
	EXPECT_EQ(expected, b1);
}

#include "../Math/Space3d.h"

TYPED_TEST(Box3dTest, TestToSpace3d)
{
	using T = TypeParam;
	Box3d<T> box(Vector3d<T>(-1, -1, -1), Vector3d<T>(2, 2, 2));
	const auto& actual = box.toSpace();
	Space3d<T> expected(Vector3d<T>(-1, -1, -1), Vector3d<T>(3, 3, 3));
	EXPECT_EQ(expected, actual);
}

TYPED_TEST(Box3dTest, TestToSurfacePositions)
{
	using T = TypeParam;
	Box3d<T> box(Vector3d<T>(0, 0, 0), Vector3d<T>(2, 2, 2));
	const auto& actual = box.toSurfacePositions(1.0f);
	EXPECT_EQ(24, actual.size());
	EXPECT_EQ(Vector3d<T>(0.5, 0.5, 0.5), actual[0]);
	EXPECT_EQ(Vector3d<T>(0.5, 0.5, 1.5), actual[1]);
	EXPECT_EQ(Vector3d<T>(0.5, 1.5, 0.5), actual[2]);
	EXPECT_EQ(Vector3d<T>(0.5, 1.5, 1.5), actual[3]);
	EXPECT_EQ(Vector3d<T>(1.5, 0.5, 0.5), actual[4]);
	EXPECT_EQ(Vector3d<T>(1.5, 0.5, 1.5), actual[5]);
	EXPECT_EQ(Vector3d<T>(1.5, 1.5, 0.5), actual[6]);
	EXPECT_EQ(Vector3d<T>(1.5, 1.5, 1.5), actual[7]);

}