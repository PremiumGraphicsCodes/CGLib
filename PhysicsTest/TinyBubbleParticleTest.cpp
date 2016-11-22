#include "gtest\gtest.h"
#include "../Physics/TinyBubbleParticle.h"

#include "../Physics/SPHConstant.h"
#include "../Physics/PBSPHParticle.h"
#include "../Physics/BubbleParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(TinyBubbleParticleTest, TestIntegrate)
{
	PBSPHConstant constant(1.0f, 0.0f, 1.0f);
	PBSPHParticle parent(Vector3d<float>(0, 0, 0), 0.5f, &constant);
	BubbleParticle bp(&parent);

	TinyBubbleParticle particle(Vector3d<float>(0,0,0), Vector3d<float>(0,0,0), &bp);
	particle.integrate(Vector3d<float>(0.0, -9.8f, 0.0), 1.0f);
	EXPECT_EQ(Vector3d<float>(0.0, -0.098f, 0.0), particle.getVelocity());
	EXPECT_EQ(Vector3d<float>(0.0, -0.098f, 0.0), particle.getPosition());
}