#include "gtest/gtest.h"

#include "../Physics/ParticlePair.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(ParticlePairTest, TestIsValid)
{
	{
		const ParticlePair pair;
		EXPECT_EQ(nullptr, pair.getParticle1());
		EXPECT_EQ(nullptr, pair.getParticle2());
		EXPECT_FALSE(pair.isValid());
	}

	{
		const auto p = std::make_shared< SPHParticle >();
		const ParticlePair pair(p.get(), p.get());
		EXPECT_FALSE(pair.isValid());
	}
	
	{
		const auto p1 = std::make_shared< SPHParticle >();
		const auto p2 = std::make_shared< SPHParticle >();
		const ParticlePair pair(p1.get(), p2.get());

		EXPECT_EQ(p1.get(), pair.getParticle1());
		EXPECT_EQ(p2.get(), pair.getParticle2());
		EXPECT_TRUE(pair.isValid());
	}
}

TEST(ParticlePairTest, TestGetDistanceSquared)
{
	const auto p1 = std::make_shared< SPHParticle >( Vector3d<float>( 0, 0, 0 ));
	const auto p2 = std::make_shared< SPHParticle >( Vector3d<float>( 1, 1, 1 ));

	const ParticlePair pair(p1.get(), p2.get());
	EXPECT_FLOAT_EQ(3, pair.getDistanceSquared());
}

TEST(ParticlePairTest, TestGetDistance)
{
	const auto p1 = std::make_shared< SPHParticle >(Vector3d<float>(0, 0, 0));
	const auto p2 = std::make_shared< SPHParticle >(Vector3d<float>(1, 1, 1));

	const ParticlePair pair(p1.get(), p2.get());
	EXPECT_FLOAT_EQ(std::sqrt(3.0f), pair.getDistance());
}

TEST(ParticlePairTest, TestGetDistanceVector)
{
	const auto p1 = std::make_shared< SPHParticle >(Vector3d<float>(1, 2, 3));
	const auto p2 = std::make_shared< SPHParticle >(Vector3d<float>(0, 0, 0));

	const ParticlePair pair(p1.get(), p2.get());
	const auto actual = pair.getDistanceVector();
	const auto expected = Vector3d<float>(1, 2, 3);
	EXPECT_EQ(actual, expected);
}