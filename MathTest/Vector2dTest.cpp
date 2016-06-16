#include "gtest\gtest.h"
#include "../Math/Vector2d.h"

using namespace Crystal::Math;

TEST(Vector2dTest, TestGetLength)
{
	using T = float;
	EXPECT_FLOAT_EQ(1, Vector2d<T>(1, 0).getLength());
	EXPECT_FLOAT_EQ(std::sqrt(2.0f), Vector2d<T>(1, 1).getLength());
	EXPECT_FLOAT_EQ(std::sqrt(5.0f), Vector2d<T>(2, 1).getLength());
}

TEST(Vector2dTest, TestGetLengthSquared)
{
	using T = float;
	EXPECT_FLOAT_EQ(1, Vector2d<T>(1, 0).getLengthSquared());
	EXPECT_FLOAT_EQ(2.0f, Vector2d<T>(1, 1).getLengthSquared());
	EXPECT_FLOAT_EQ(5.0f, Vector2d<T>(2, 1).getLengthSquared());
}

TEST(Vector2dTest, TestGetAngle)
{
	using T = float;
	EXPECT_EQ(Angle<T>(Degree<T>(  0)), Vector2d<T>( 1, 0).getAngle());
	EXPECT_EQ(Angle<T>(Degree<T>(180)), Vector2d<T>(-1, 0).getAngle());
	EXPECT_EQ(Angle<T>(Degree<T>( 90)), Vector2d<T>( 0, 1).getAngle());

	EXPECT_EQ(Angle<T>(Degree<T>( 45)), Vector2d<T>( 1, 1).getAngle());
	EXPECT_EQ(Angle<T>(Degree<T>(-45)), Vector2d<T>( 1,-1).getAngle());
}

TEST(Vector2dTest, TestGetAngleByVector)
{
	using T = float;
	EXPECT_EQ(Angle<T>(Degree<T>( 0)), Vector2d<T>(1, 0).getAngle(Vector2d<T>(1, 0)));
	EXPECT_EQ(Angle<T>(Degree<T>(90)), Vector2d<T>(1, 0).getAngle(Vector2d<T>(0, 1)));
	EXPECT_EQ(Angle<T>(Degree<T>(90)), Vector2d<T>(1, 0).getAngle(Vector2d<T>(0, -1)));
}

TEST(Vector2dTest, TestGetSignedAngleByVector)
{
	using T = float;
	EXPECT_EQ(Angle<T>(Degree<T>(0)), Vector2d<T>(1, 0).getSignedAngle(Vector2d<T>(1, 0)));
	EXPECT_EQ(Angle<T>(Degree<T>(90)), Vector2d<T>(1, 0).getSignedAngle(Vector2d<T>(0, 1)));
	EXPECT_EQ(Angle<T>(Degree<T>(-90)), Vector2d<T>(1, 0).getSignedAngle(Vector2d<T>(0, -1)));
}


TEST(Vector2dTest, TestIsLeft)
{
	using T = float;
	EXPECT_TRUE( Vector2d<T>(1, 0).isLeft(Vector2d<T>(0, 1)) );
	EXPECT_FALSE(Vector2d<T>(-1, 0).isLeft(Vector2d<T>(0, 1)));
	EXPECT_FALSE( Vector2d<T>(0, 1).isLeft(Vector2d<T>(1, 0)) );
}

TEST(Vector2dTest, TestIsRight)
{
	using T = float;
	EXPECT_FALSE(Vector2d<T>(1, 0).isRight(Vector2d<T>(0, 1)));
	EXPECT_TRUE(Vector2d<T>(-1, 0).isRight(Vector2d<T>(0, 1)));
	EXPECT_TRUE(Vector2d<T>(0, 1).isRight(Vector2d<T>(1, 0)));
}