#include "gtest\gtest.h"
#include "../Math/PolyLine3d.h"

using namespace Crystal::Math;

TEST(Polyline3dTest, TestAdd)
{
	Polyline3d<float> pl;
	pl.add(Vector3d<float>(1, 2, 3));
	EXPECT_EQ(1, pl.size());
}