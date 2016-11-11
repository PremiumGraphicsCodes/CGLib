#include "gtest/gtest.h"

#include "../Physics/BubbleParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(BubbleParticleTest, TestGetTrappedAirPotential)
{
	const BubbleParticle p1(Vector3d<float>(0,0,0), Vector3d<float>(0,0,0), Vector3d<float>(1,0,0), 1.0f);
	const BubbleParticle p2(Vector3d<float>(1,0,0), Vector3d<float>(-1,0,0), Vector3d<float>(1,0,0), 1.0f);
	const auto actual = p1.getTrappedAirPotential(p2, 2.0);
}

TEST(BubbleParticleTest, TestGetCurvature)
{
	const BubbleParticle p1(Vector3d<float>(0, 0, 0), Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0), 1.0f);
	const BubbleParticle p2(Vector3d<float>(1, 0, 0), Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), 1.0f);
	const auto actual = p1.getCurvature(p2, 2.0);
}

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