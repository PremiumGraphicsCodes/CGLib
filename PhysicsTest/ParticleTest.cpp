#include "gtest/gtest.h"

#include "../Physics/SPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;


TEST(SPHParticleTest, TestConstruct)
{
	const SPHParticle particle;
	EXPECT_EQ(Vector3d<float>(0.0f, 0.0f, 0.0f), particle.getPosition());
}

TEST(SPHParticleTest, TestConstructByPosition)
{
	const SPHParticle particle(Vector3d<float>(1.0f, 2.0f, 3.0f), 0.5f, 1.0f);
	EXPECT_EQ(Vector3d<float>(1.0f, 2.0f, 3.0f), particle.getPosition());
}

