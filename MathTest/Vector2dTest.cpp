#include "gtest\gtest.h"
#include "../Math/Vector2d.h"

using namespace Crystal::Math;

TEST(Vector2dTest, TestGetLength)
{
	using T = float;
	EXPECT_EQ(1, Vector2d<T>(1, 0).getLength());
	EXPECT_FLOAT_EQ(std::sqrt(2.0f), Vector2d<T>(1, 1).getLength());

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