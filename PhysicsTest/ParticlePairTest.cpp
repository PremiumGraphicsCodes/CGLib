#include "gtest/gtest.h"

#include "../Physics/ParticlePair.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(ParticlePairTest, TestIsValid)
{
	{
		const SPHParticlePair pair;
		EXPECT_EQ(nullptr, pair.getParticle1());
		EXPECT_EQ(nullptr, pair.getParticle2());
		EXPECT_FALSE(pair.isValid());
	}

	{
		const auto p = std::make_shared< SPHParticle >();
		const SPHParticlePair pair(p.get(), p.get());
		EXPECT_FALSE(pair.isValid());
	}
	
	{
		const auto p1 = std::make_shared< SPHParticle >();
		const auto p2 = std::make_shared< SPHParticle >();
		const SPHParticlePair pair(p1.get(), p2.get());

		EXPECT_EQ(p1.get(), pair.getParticle1());
		EXPECT_EQ(p2.get(), pair.getParticle2());
		EXPECT_TRUE(pair.isValid());
	}
}

TEST(SPHParticlePairTest, TestGetDistanceSquared)
{
	SPHConstant constant;
	SPHParticle p1( Vector3d<float>( 0, 0, 0 ), 0.5f, 1.0f, &constant);
	SPHParticle p2( Vector3d<float>( 1, 1, 1 ), 0.5f, 1.0f, &constant);

	const SPHParticlePair pair(&p1, &p2);
	EXPECT_FLOAT_EQ(3, pair.getDistanceSquared());
}

TEST(SPHParticlePairTest, TestGetDistance)
{
	SPHConstant constant;
	SPHParticle p1(Vector3d<float>(0, 0, 0), 0.5f, 1.0f, &constant);
	SPHParticle p2(Vector3d<float>(1, 1, 1), 0.5f, 1.0f, &constant);

	const SPHParticlePair pair(&p1, &p2);
	EXPECT_FLOAT_EQ(std::sqrt(3.0f), pair.getDistance());
}

TEST(SPHParticlePairTest, TestGetDistanceVector)
{
	SPHConstant constant;
	SPHParticle p1(Vector3d<float>(1, 2, 3), 0.5f, 1.0f, &constant);
	SPHParticle p2(Vector3d<float>(0, 0, 0), 0.5f, 1.0f, &constant);

	const SPHParticlePair pair(&p1, &p2);
	const auto actual = pair.getDistanceVector();
	const auto expected = Vector3d<float>(1, 2, 3);
	EXPECT_EQ(actual, expected);
}