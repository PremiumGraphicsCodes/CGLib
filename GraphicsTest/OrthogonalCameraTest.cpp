#include "gtest/gtest.h"

#include "../Graphics/OrthogonalCamera.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;

using T = float;

TEST(OrthogonalCameraTest, TestGetProjectionMatrix)
{
	const OrthogonalCamera<float> c;
	const Matrix4d<float>& m = c.getProjectionMatrix();

	EXPECT_EQ(2, m.getX00());
	EXPECT_EQ(2, m.getX11());
}