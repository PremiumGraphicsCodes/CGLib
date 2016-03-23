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

TEST(SPHParticleTest, TestAddSelfDensity)
{
	SPHParticle particle(Vector3d<float>(1.0f, 2.0f, 3.0f), 0.5f, 1000.0f, 1.0f, 1.0f);
	particle.init();
	particle.addSelfDensity(1.25f);
	const auto actual = particle.getDensity();
	EXPECT_TRUE(actual > 800.0f);
	EXPECT_TRUE(actual < 1000.0f);
}

TEST(SPHParticleTest, TestSolveNormal)
{
	SPHParticle particle1(Vector3d<float>(1.0f, 2.0f, 3.0f), 0.5f, 1000.0f, 1.0f, 1.0f);
	SPHParticle particle2(Vector3d<float>(2.0f, 2.0f, 3.0f), 0.5f, 1000.0f, 1.0f, 1.0f);
	particle1.setTensionCoe(1.0f);
	particle2.setTensionCoe(1.0f);
	particle1.init();
	particle2.init();
	particle1.addSelfDensity(1.25f);
	particle2.addSelfDensity(1.25f);
	particle1.solveNormal(particle2, 1.25f);
	particle2.solveNormal(particle1, 1.25f);

	EXPECT_TRUE(particle1.getNormal().getX() < 0.0f);
	EXPECT_EQ(particle1.getNormal().getX(), -particle2.getNormal().getX());

	particle1.solveSurfaceTension(particle2, 1.25f);
	const auto actual = particle1.getForce().getX();
	EXPECT_TRUE(actual > 0.0f);
}