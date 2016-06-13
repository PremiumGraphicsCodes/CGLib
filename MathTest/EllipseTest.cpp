#include "gtest\gtest.h"

#include "../Math/Ellipse.h"

using namespace Crystal::Math;

TEST(EllipseTest, TestGetPosition)
{
	Ellipse<float> e(Vector2d<float>(1,0.5));
	EXPECT_EQ(Vector2d<float>(1, 0), e.getPosition(Angle<float>(Degree<float>(0))));
	EXPECT_EQ(Vector2d<float>(0, 0.5), e.getPosition(Angle<float>(Degree<float>(90))));

}

TEST(EllipseTest, TestGetNormal)
{
	Ellipse<float> e(Vector2d<float>(1, 0.5));
	EXPECT_EQ(Vector2d<float>(1, 0), e.getNormal(Angle<float>(Degree<float>(0))));
	EXPECT_EQ(Vector2d<float>(0, 1), e.getNormal(Angle<float>(Degree<float>(90))));

}