#include "gtest\gtest.h"
#include "../Physics/BubbleGenerator.h"
#include "../Physics/PBSPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(BubbleGeneratorTest, TestGenerate)
{
	PBSPHConstant constant(1000.0f, 0.0f, 1.0f);
	PBSPHParticle particle1(Vector3d<float>(0,0,0), 0.5f, &constant);
	PBSPHParticle particle2(Vector3d<float>(1,0,0), 0.5f, &constant);

	particle1.setVelocity(Vector3d<float>(1.0, 0.0, 0.0));
	particle1.setNeighbors({ &particle2 });
	BubbleGenerator generator({&particle1});
	generator.generate(2.0f, 1.0f);
	EXPECT_EQ(1, generator.getTinys().size());
}