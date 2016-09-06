#include "gtest\gtest.h"
#include "../Math/Vector2d.h"

using namespace Crystal::Math;

template<class T>
class Vector2dTest : public testing::Test {
};

typedef ::testing::Types<float, double> TestTypes;

TYPED_TEST_CASE(Vector2dTest, TestTypes);

TYPED_TEST(Vector2dTest, TestScaled)
{
	using T = TypeParam;
	Vector2d<T> v(1, 2);
	EXPECT_EQ( Vector2d<T>(2,4), v.scaled(2));
}

TYPED_TEST(Vector2dTest, TestGetLength)
{
	using T = TypeParam;
	EXPECT_EQ(1, Vector2d<T>(1, 0).getLength());
	EXPECT_EQ(std::sqrt(T{ 2 }), Vector2d<T>(1, 1).getLength());
	EXPECT_EQ(std::sqrt(T{ 5 }), Vector2d<T>(2, 1).getLength());
}

TYPED_TEST(Vector2dTest, TestGetLengthSquared)
{
	using T = TypeParam;
	EXPECT_EQ(T{ 1 }, Vector2d<T>(1, 0).getLengthSquared());
	EXPECT_EQ(T{ 2 }, Vector2d<T>(1, 1).getLengthSquared());
	EXPECT_EQ(T{ 5 }, Vector2d<T>(2, 1).getLengthSquared());
}

TYPED_TEST(Vector2dTest, TestGetAngle)
{
	using T = TypeParam;
	EXPECT_EQ(Angle<T>(Degree<T>(  0)), Vector2d<T>( 1, 0).getAngle());
	EXPECT_EQ(Angle<T>(Degree<T>(180)), Vector2d<T>(-1, 0).getAngle());
	EXPECT_EQ(Angle<T>(Degree<T>( 90)), Vector2d<T>( 0, 1).getAngle());

	EXPECT_EQ(Angle<T>(Degree<T>( 45)), Vector2d<T>( 1, 1).getAngle());
	EXPECT_EQ(Angle<T>(Degree<T>(-45)), Vector2d<T>( 1,-1).getAngle());
}

TYPED_TEST(Vector2dTest, TestGetAngleByVector)
{
	using T = TypeParam;
	EXPECT_EQ(Angle<T>(Degree<T>( 0)), Vector2d<T>(1, 0).getAngle(Vector2d<T>(1, 0)));
	EXPECT_EQ(Angle<T>(Degree<T>(90)), Vector2d<T>(1, 0).getAngle(Vector2d<T>(0, 1)));
	EXPECT_EQ(Angle<T>(Degree<T>(90)), Vector2d<T>(1, 0).getAngle(Vector2d<T>(0, -1)));
}

TYPED_TEST(Vector2dTest, TestGetSignedAngleByVector)
{
	using T = TypeParam;
	EXPECT_EQ(Angle<T>(Degree<T>(0)), Vector2d<T>(1, 0).getSignedAngle(Vector2d<T>(1, 0)));
	EXPECT_EQ(Angle<T>(Degree<T>(90)), Vector2d<T>(1, 0).getSignedAngle(Vector2d<T>(0, 1)));
	EXPECT_EQ(Angle<T>(Degree<T>(-90)), Vector2d<T>(1, 0).getSignedAngle(Vector2d<T>(0, -1)));
}

TYPED_TEST(Vector2dTest, TestIsLeft)
{
	using T = TypeParam;
	EXPECT_TRUE( Vector2d<T>( 1, 0).isLeft(Vector2d<T>(0, 1)) );
	EXPECT_FALSE(Vector2d<T>(-1, 0).isLeft(Vector2d<T>(0, 1)) );
	EXPECT_FALSE(Vector2d<T>( 0, 1).isLeft(Vector2d<T>(1, 0)) );
}

TYPED_TEST(Vector2dTest, TestIsRight)
{
	using T = TypeParam;
	EXPECT_FALSE(Vector2d<T>( 1, 0).isRight(Vector2d<T>(0, 1)));
	EXPECT_TRUE( Vector2d<T>(-1, 0).isRight(Vector2d<T>(0, 1)));
	EXPECT_TRUE( Vector2d<T>( 0, 1).isRight(Vector2d<T>(1, 0)));
}