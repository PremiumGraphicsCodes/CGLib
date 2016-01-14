#include "gtest/gtest.h"

#include "../Graphics/PerspectiveCamera.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

using T = float;

TEST(PerspectiveCameraTest, TestGetProjectionMatrix)
{
	const PerspectiveCamera<float> c;
	const auto& m = c.getProjectionMatrix();

	EXPECT_EQ(1, m.getX00());
	EXPECT_EQ(0, m.getX01());
	EXPECT_EQ(0, m.getX02());
	EXPECT_EQ(0, m.getX03());
	EXPECT_EQ(0, m.getX10());
	EXPECT_EQ(1, m.getX11());
	EXPECT_EQ(0, m.getX12());
	EXPECT_EQ(0, m.getX13());
}