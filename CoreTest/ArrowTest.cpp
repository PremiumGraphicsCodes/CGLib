#include "stdafx.h"
#include "../Core/Arrow.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(ArrowTest, Test)
{
	const Arrow arrow(Vector3d<float>(0,0,0));
	EXPECT_EQ(Vector3d<float>(0,-0.5,0), arrow.getCylinder().getCenter());
	EXPECT_EQ(Vector3d<float>(0, 0.5, 0), arrow.getCone().getCenter());

}