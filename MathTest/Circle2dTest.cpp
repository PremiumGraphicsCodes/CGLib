#include "gtest\gtest.h"

#include "../Math/Circle2d.h"

using namespace Crystal::Math;

TEST(Circle2dTest, TestGetPosition)
{
	Circle2d<float> c(1);
	EXPECT_EQ(Vector2d<float>(1, 0), c.getPosition(Angle<float>(Degree<float>(0))));
	EXPECT_EQ(Vector2d<float>(0, 1), c.getPosition(Angle<float>(Degree<float>(90))));

}

TEST(Circle2dTest, TestGetNormal)
{
	Circle2d<float> c(1);
	EXPECT_EQ(Vector2d<float>(1, 0), c.getNormal(Angle<float>(Degree<float>(0))));
	EXPECT_EQ(Vector2d<float>(0, 1), c.getNormal(Angle<float>(Degree<float>(90))));

}