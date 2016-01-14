#include "gtest/gtest.h"

#include "Space2d.h"

using namespace Crystal::Math;

TEST(Space2dTest, TestIsIn)
{
	Space2d<float> space(Vector2d<float>(0, 0), Vector2d<float>(1, 1));
	EXPECT_TRUE( space.isIn(Vector2d<float>(0.5, 0.5) ) );
	EXPECT_FALSE(space.isIn(Vector2d<float>(1.5, 0.5) ) );

}