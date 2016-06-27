#include "gtest\gtest.h"

#include "../Math/Ellipse3d.h"

using namespace Crystal::Math;

TEST(Ellipse3dTest, TestGetPosition)
{
	const Ellipse3d<float> e(Vector3d<float>(0.5, 0.5, 0.5), Vector3d<float>(0,0,0));
	EXPECT_EQ( Vector3d<float>(0.5, 0.0, 0.0), e.getPosition(Param<float>(0)) );
	EXPECT_EQ(Vector3d<float>(-0.5, 0.0, 0.0), e.getPosition(Param<float>(0.5)));

}