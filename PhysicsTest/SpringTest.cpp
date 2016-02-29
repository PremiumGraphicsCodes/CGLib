#include "gtest/gtest.h"

#include "../Physics/Spring.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(SpringTest, Test)
{
	Spring::Param param;
	param.damperCoe = 1.0f;
	param.springCoe = 1.0f;
	param.restDistance = 1.0f;
	Particle particle1;
	Particle particle2;
	ParticlePair pair(&particle1, &particle2);
	Spring spring(pair, param);
}