#include "gtest/gtest.h"

#include "../Physics/PhysicsParticleFindAlgo.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

using GeomType = float;

TEST(NeighborSearchAlgoTest, Test)
{
	Particle particle1(Vector3d<GeomType>(0.0, 0.0, 0.0));
	Particle particle2(Vector3d<GeomType>(1.0, 0.0, 0.0));
	const std::vector<Particle*> particles{
		&particle1,
		&particle2,
	};

	{
		ParticleFindAlgo<GeomType> algo;
		algo.createPairs(particles, 1.1f);
		const auto& pairs = algo.getPairs();
		EXPECT_EQ(2, pairs.size());
	}

	{
		ParticleFindAlgo<GeomType> algo;
		algo.createPairs(particles, 0.9f);
		const auto& pairs = algo.getPairs();
		EXPECT_TRUE( pairs.empty());
	}
}