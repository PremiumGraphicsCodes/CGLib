#include "gtest\gtest.h"
#include "../Polygon/VolumeNode.h"
#include "../Polygon/Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(VolumeNodeTest, TestToParticle)
{
	const VolumeNode node( Vector3d<float>(1.0, 1.0, 1.0), 0.5f );
	const auto actual = node.toParticle(1.0f);
	const Particle expected(Vector3d<float>(1.0, 1.0, 1.0), 0.5f, 1.0f);
	EXPECT_EQ(expected, actual);
}