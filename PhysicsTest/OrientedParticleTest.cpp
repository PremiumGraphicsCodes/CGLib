#include "gtest\gtest.h"

#include "../Core/Particle.h"
#include "../Physics/OrientedParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Physics;

TEST(OrientedParticleTest, Test1)
{
	Vector3d<float> position(0, 0, 0);
	OrientedParticle particle(position, 1.0f);

	Particle p1( Vector3d<float>(0.5, 0.0, 0.0), 1.0f, 1.0f);
	std::list<IParticle*> neighbors{ &p1 };
	particle.setNeighbors(neighbors);

	EXPECT_FLOAT_EQ(0.875, particle.getTotalWeight());
	EXPECT_EQ(Vector3d<float>(0.5,0,0), particle.getWeightedMeanPosition());
}