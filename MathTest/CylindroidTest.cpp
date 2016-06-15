#include "gtest\gtest.h"

#include "../Math/Cylindroid.h"

using namespace Crystal::Math;

TEST(CylindroidTest, TestGetPosition)
{
	Cylindroid<float> c(Vector3d<float>(0, 0, 0), Vector2d<float>( 1.0, 1.0 ), 1.0);
	{
		const auto pos = c.getPosition(Param<float>(0), Param<float>(0));
		EXPECT_EQ(Vector3d<float>(1, -0.5, 0), pos);
	}
	/*
	{
		const auto pos = cylinder.getPosition(Param<float>(0), Param<float>(1));
		EXPECT_EQ(Vector3d<float>(1, 0.5, 0), pos);
	}
	*/
}
