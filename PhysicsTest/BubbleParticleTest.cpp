#include "gtest/gtest.h"

#include "../Physics/BubbleParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(BubbleParticleTest, TestGetTrappedAirPotential)
{
	SPHConstant constant(1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	PBSPHParticle parent1(Vector3d<float>(0, 0, 0), 0.5f, &constant);
	PBSPHParticle parent2(Vector3d<float>(1, 0, 0), 0.5f, &constant);
	parent1.setVelocity(Vector3d<float>(0, 1, 0));
	parent2.setVelocity(Vector3d<float>(0, -1, 0));
	const BubbleParticle p1(&parent1);
	const BubbleParticle p2(&parent2);
	const auto actual = p1.getTrappedAirPotential(parent2, 2.0);
	EXPECT_FLOAT_EQ(0.5f, actual);
}

TEST(BubbleParticleTest, TestGetCurvature)
{
	SPHConstant constant(1.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	PBSPHParticle parent1(Vector3d<float>(0, 0, 0), 0.5f, &constant);
	PBSPHParticle parent2(Vector3d<float>(1, 0, 0), 0.5f, &constant);
	parent1.setNormal(Vector3d<float>(-1, 0, 0));
	parent2.setNormal(Vector3d<float>(1, 0, 0));
	const BubbleParticle p1(&parent1);
	const BubbleParticle p2(&parent2);
	const auto actual = p1.getCurvature(parent2, 2.0);
	EXPECT_FLOAT_EQ(1.5f, actual);
}
/*
TEST(BubbleParticleTest, TestGetMovingDirectionCoe)
{
	const BubbleParticle p1(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(1, 0, 0), 1.0f);
	EXPECT_EQ(1.0f, p1.getMovingDirectionCoe());
}

TEST(BubbleParticleTest, TestGetKineticEnegy)
{
	const BubbleParticle p1(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(1, 0, 0), 1.0f);
	EXPECT_EQ(0.5f, p1.getKineticEnegy());
}
*/