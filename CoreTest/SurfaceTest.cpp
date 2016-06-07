#include "gtest\gtest.h"
#include "../Core/Surface.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(SurfaceTest, Test)
{
	Curve3d<float> curve(2,2);
	curve.setPosition(0, 0, Vector3d<float>(0, 0, 0));
	curve.setPosition(0, 1, Vector3d<float>(0, 1, 0));
	curve.setPosition(1, 0, Vector3d<float>(1, 0, 0));
	curve.setPosition(1, 1, Vector3d<float>(1, 1, 0));

	Surface surface(curve);
	EXPECT_EQ(6, surface.getEdges().size());
	EXPECT_EQ(4, surface.getNodes().size());
	EXPECT_EQ(2, surface.getFaces().size());

}