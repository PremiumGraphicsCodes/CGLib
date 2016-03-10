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
	SPHParticle particle1;
	SPHParticle particle2;
	SPHParticlePair pair(&particle1, &particle2);
	Spring spring(pair, param);
	spring.coordinate(1.0f);
}