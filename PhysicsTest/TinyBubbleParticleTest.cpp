#include "gtest\gtest.h"
#include "../Physics/TinyParticle.h"

#include "../Physics/SPHConstant.h"
#include "../Physics/PBSPHParticle.h"
#include "../Physics/BubbleParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(TinyBubbleParticleTest, TestUpdateVelocity)
{
	SPHConstant constant(1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	PBSPHParticle parent(Vector3d<float>(0, 0, 0), 0.5f, &constant);
	BubbleParticle bp(&parent);

	TinyBubbleParticle particle(Vector3d<float>(0,0,0), Vector3d<float>(0,0,0), &bp);
	particle.updateVelocity(1.0, Vector3d<float>(0.0, -9.8, 0.0));
	EXPECT_EQ(Vector3d<float>(0.0, -0.098, 0.0), particle.getVelocity());
}