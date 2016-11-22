#include "gtest/gtest.h"

#include "../Physics/BubbleParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(BubbleParticleTest, TestGetTrappedAirPotential)
{
	PBSPHConstant constant(1.0f, 0.0f, 1.0f);
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
	PBSPHConstant constant(1.0f, 0.0f, 1.0f);
	PBSPHParticle parent1(Vector3d<float>(0, 0, 0), 0.5f, &constant);
	PBSPHParticle parent2(Vector3d<float>(1, 0, 0), 0.5f, &constant);
	parent1.setNormal(Vector3d<float>(-1, 0, 0));
	parent2.setNormal(Vector3d<float>(1, 0, 0));
	const BubbleParticle p1(&parent1);
	const BubbleParticle p2(&parent2);
	const auto actual = p1.getCurvature(parent2, 2.0);
	EXPECT_FLOAT_EQ(1.5f, actual);
}

TEST(BubbleParticleTest, TestGetMovingDirectionCoe)
{
	PBSPHConstant constant(1.0f,0.0f, 1.0f);
	PBSPHParticle parent1(Vector3d<float>(0, 0, 0), 0.5f, &constant);
	parent1.setVelocity(Vector3d<float>(0, 1, 0));
	parent1.setNormal(Vector3d<float>(0, 1, 0));

	const BubbleParticle p1(&parent1);
	EXPECT_FLOAT_EQ(1.0f, p1.getMovingDirectionCoe());
}

TEST(BubbleParticleTest, TestGetKineticEnegy)
{
	PBSPHConstant constant(1.0f, 0.0f,1.0f);
	PBSPHParticle parent1(Vector3d<float>(0, 0, 0), 0.5f, &constant);
	parent1.setVelocity(Vector3d<float>(0, 1, 0));
	const BubbleParticle p1(&parent1);
	EXPECT_FLOAT_EQ(0.5f, p1.getKineticEnegy());
}

TEST(BubbleParticleTest, TestSolveTrappedAirPotential)
{
	PBSPHConstant constant(1000.0f, 0.0f, 1.0f);
	PBSPHParticle parent1(Vector3d<float>(0, 0, 0), 0.5f, &constant);
	parent1.setVelocity(Vector3d<float>(0, 1, 0));
	PBSPHParticle parent2(Vector3d<float>(1, 0, 0), 0.5f, &constant);
	parent2.setVelocity(Vector3d<float>(0, -1, 0));

	BubbleParticle p1(&parent1);
	parent1.addNeighbor(&parent2);
	p1.solveTrappedAirPotential(2.0f);
	EXPECT_EQ(0.5f, p1.getTotalTrappedAirPotential());
	p1.clampTrappedAirPotential();
	EXPECT_EQ(0.0f, p1.getTotalTrappedAirPotential());
}

TEST(BubbleParticleTest, TestSolveWaveCrestPotential)
{
	PBSPHConstant constant(1.0f, 0.0f, 1.0f);
	PBSPHParticle parent1(Vector3d<float>(0, 0, 0), 0.5f, &constant);
	PBSPHParticle parent2(Vector3d<float>(1, 0, 0), 0.5f, &constant);
	parent1.setNormal(Vector3d<float>(-1, 0, 0));
	parent2.setNormal(Vector3d<float>(1, 0, 0));
	parent1.setNeighbors({ &parent2 });
	BubbleParticle p1(&parent1);
	const BubbleParticle p2(&parent2);
	p1.solveWaveCrestPotential(2.0f);
	EXPECT_EQ(1.5f, p1.getTotalWeveCrestPotential());
	p1.clampWaveCrestPotential();
	EXPECT_EQ(0.0f, p1.getTotalWeveCrestPotential());
}


TEST(BubbleParticleTest, TestGenerateParticleNumberByTrappedAir)
{
	PBSPHConstant constant(1000.0f, 0.0f, 1.0f);
	PBSPHParticle parent1(Vector3d<float>(0, 0, 0), 0.5f, &constant);
	parent1.setVelocity(Vector3d<float>(0, 1, 0));
	PBSPHParticle parent2(Vector3d<float>(1, 0, 0), 0.5f, &constant);
	parent2.setVelocity(Vector3d<float>(0, -1, 0));
	parent1.setNeighbors({ &parent2 });

	BubbleParticle p1(&parent1);
	p1.solveTrappedAirPotential(2.0f);
	p1.solveWaveCrestPotential(2.0f);
	p1.solveKineticEnergy();

	EXPECT_FLOAT_EQ(0.5f, p1.getGenerateParticleNumber(1.0f, 0.0f, 1.0f));
}

TEST(BubbleParticleTest, TestGenerateParticleNumberByWaveCrest)
{
	PBSPHConstant constant(1000.0f, 0.0f, 1.0f);
	PBSPHParticle parent1(Vector3d<float>(0, 0, 0), 0.5f, &constant);
	PBSPHParticle parent2(Vector3d<float>(1, 0, 0), 0.5f, &constant);
	parent1.setVelocity(Vector3d<float>(0, 1, 0));
	parent1.setNormal(Vector3d<float>(-1, 0, 0));
	parent2.setNormal(Vector3d<float>(1, 0, 0));
	parent1.setNeighbors({ &parent2 });

	BubbleParticle p1(&parent1);
	p1.solveTrappedAirPotential(2.0f);
	p1.solveWaveCrestPotential(2.0f);
	p1.solveKineticEnergy();

	EXPECT_FLOAT_EQ(1.5f, p1.getGenerateParticleNumber(0.0f, 1.0f, 1.0f));
}