#include "gtest/gtest.h"
#include "../Physics/IndexedParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(IndexedParticleTest, Test)
{
	SPHParticle particle1;
	IndexedParticle iparticle1(&particle1);
	iparticle1.setGridID(1.0f);
	EXPECT_EQ(0, iparticle1.getGridID());

	SPHConstant constant;
	SPHParticle particle2( Vector3d<float>(1.5f, 0.0f, 0.0f), 0.5f, &constant);
	IndexedParticle iparticle2(&particle2);
	iparticle2.setGridID(1.0f);
	EXPECT_EQ(1, iparticle2.getGridID());
}