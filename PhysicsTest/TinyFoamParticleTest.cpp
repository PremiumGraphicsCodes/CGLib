#include "gtest\gtest.h"
#include "../Physics/TinyParticle.h"

#include "../Physics/SPHConstant.h"
#include "../Physics/PBSPHParticle.h"
#include "../Physics/BubbleParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(TinyFoamParticleTest, TestIntegrate)
{
	PBSPHConstant constant(1.0f, 0.0f, 1.0f);
	PBSPHParticle parent(Vector3d<float>(0, 0, 0), 0.5f, &constant);
	BubbleParticle bp(&parent);

	TinyFoamParticle particle(Vector3d<float>(0, 0, 0), Vector3d<float>(0, 0, 0), &bp);
	particle.integrate(Vector3d<float>(0.0, -9.8, 0.0), 1.0);
	EXPECT_EQ(Vector3d<float>(0.0, 0.0, 0.0), particle.getVelocity());
	EXPECT_EQ(Vector3d<float>(0.0, 0.0, 0.0), particle.getPosition());
}