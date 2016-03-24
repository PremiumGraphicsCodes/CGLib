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
	SPHConstant constant;
	const SPHParticle particle(Vector3d<float>(1.0f, 2.0f, 3.0f), 0.5f, 1.0f, &constant);
	EXPECT_EQ(Vector3d<float>(1.0f, 2.0f, 3.0f), particle.getPosition());
}

TEST(SPHParticleTest, TestAddSelfDensity)
{
	SPHConstant constant;
	SPHParticle particle(Vector3d<float>(1.0f, 2.0f, 3.0f), 0.5f, 1000.0f, &constant);
	particle.init();
	particle.addSelfDensity();
	const auto actual = particle.getDensity();
	EXPECT_TRUE(actual > 800.0f);
	EXPECT_TRUE(actual < 1000.0f);
}

TEST(SPHParticleTest, TestSolveNormal)
{
	SPHConstant constant(1.0f, 0.0f, 1.0f, 1.25f);

	SPHParticle particle1(Vector3d<float>(1.0f, 2.0f, 3.0f), 0.5f, 1000.0f, &constant);
	SPHParticle particle2(Vector3d<float>(2.0f, 2.0f, 3.0f), 0.5f, 1000.0f, &constant);
	particle1.init();
	particle2.init();
	particle1.addSelfDensity();
	particle2.addSelfDensity();
	particle1.solveNormal(particle2);
	particle2.solveNormal(particle1);

	EXPECT_TRUE(particle1.getNormal().getX() < 0.0f);
	EXPECT_EQ(particle1.getNormal().getX(), -particle2.getNormal().getX());

	particle1.solveSurfaceTension(particle2);
	const auto actual = particle1.getForce().getX();
	EXPECT_TRUE(actual > 0.0f);
}

TEST(SPHParticleTest, TestFreeFall)
{
	SPHConstant constant;
	SPHParticle particle(Vector3d<float>(0.0f, 0.0f, 0.0f), 0.5f, 1000.0f, &constant);
	particle.addSelfDensity();
	particle.addExternalForce(Vector3d<float>(0.0, -10.0f, 0.0f));
	particle.forwardTime(0.1f);
	const auto position = particle.getPosition();
}