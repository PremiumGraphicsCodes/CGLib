#include "gtest/gtest.h"

#include "../Physics/ParticlePair.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

using GeomType = float;

TEST(ParticlePairTest, TestIsValid)
{
	{
		const ParticlePair<GeomType> pair;
		EXPECT_EQ(nullptr, pair.getParticle1());
		EXPECT_EQ(nullptr, pair.getParticle2());
		EXPECT_FALSE(pair.isValid());
	}

	{
		const auto p = std::make_shared< Particle >();
		const ParticlePair<GeomType> pair(p.get(), p.get());
		EXPECT_FALSE(pair.isValid());
	}
	
	{
		const auto p1 = std::make_shared< Particle >();
		const auto p2 = std::make_shared< Particle >();
		const ParticlePair<GeomType> pair(p1.get(), p2.get());

		EXPECT_EQ(p1.get(), pair.getParticle1());
		EXPECT_EQ(p2.get(), pair.getParticle2());
		EXPECT_TRUE(pair.isValid());
	}
}

TEST(ParticlePairTest, TestGetDistanceSquared)
{
	const auto p1 = std::make_shared< Particle >( Vector3d<GeomType>( 0, 0, 0 ));
	const auto p2 = std::make_shared< Particle >( Vector3d<GeomType>( 1, 1, 1 ));

	const ParticlePair<GeomType> pair(p1.get(), p2.get());
	EXPECT_FLOAT_EQ(3, pair.getDistanceSquared());
}

TEST(ParticlePairTest, TestGetDistance)
{
	const auto p1 = std::make_shared< Particle >(Vector3d<GeomType>(0, 0, 0));
	const auto p2 = std::make_shared< Particle >(Vector3d<GeomType>(1, 1, 1));

	const ParticlePair<GeomType> pair(p1.get(), p2.get());
	EXPECT_FLOAT_EQ(std::sqrt(GeomType{ 3 }), pair.getDistance());
}

TEST(ParticlePairTest, TestGetDistanceVector)
{
	const auto p1 = std::make_shared< Particle >(Vector3d<GeomType>(1, 2, 3));
	const auto p2 = std::make_shared< Particle >(Vector3d<GeomType>(0, 0, 0));

	const ParticlePair<GeomType> pair(p1.get(), p2.get());
	const auto actual = pair.getDistanceVector();
	const auto expected = Vector3d<GeomType>(1, 2, 3);
	EXPECT_EQ(actual, expected);
}