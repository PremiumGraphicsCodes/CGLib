#include "stdafx.h"

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

TEST(OrthogonalCameraTest, TestGetPosition)
{
	OrthogonalCamera<float> c;
	c.setRect(-0.5, 0.5, -0.5, 0.5);
	c.getPosition(Vector3d<float>(1, 1, 1));
}