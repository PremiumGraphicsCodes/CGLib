#include "stdafx.h"
#include "../Core/Joint.h"
#include "../Core/AnisotoropicParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(JointTest, TestToParticle)
{
	Vector3d<float> size(0.5, 0.5, 0.5);
	Joint joint( Vector3d<float>(1.0, 0.0, 0.0), size);
	const auto& actual = joint.toParticle(0.5f);
	EXPECT_EQ(Vector3d<float>(1.0, 0.0, 0.0), actual.getPosition());
	EXPECT_EQ(0.5f, actual.getDensity());
}

