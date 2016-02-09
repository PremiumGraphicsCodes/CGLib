#include "gtest/gtest.h"
#include "../Polygon/Joint.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

TEST(JointTest, Test)
{
	Joint joint( Vector3d<float>(1.0, 0.0, 0.0), 0.5f, 1.0f);
	const Particle& actual = joint.toParticle();
	EXPECT_EQ(Vector3d<float>(1.0, 0.0, 0.0), actual.getPosition());
	EXPECT_EQ(1.0f, actual.getDensity());
}