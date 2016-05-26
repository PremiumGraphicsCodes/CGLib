#include "gtest/gtest.h"
#include "../Polygon/Joint.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(JointTest, Test)
{
	Joint joint( Vector3d<float>(1.0, 0.0, 0.0), 0.5);
	const Particle& actual = joint.toParticle(0.5f);
	EXPECT_EQ(Vector3d<float>(1.0, 0.0, 0.0), actual.getPosition());
	EXPECT_EQ(0.5f, actual.getDensity());
}