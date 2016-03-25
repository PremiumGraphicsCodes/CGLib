#include "gtest/gtest.h"

#include "../Physics/IndexedFinder.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

TEST(IndexedFinderTest, Test)
{
	SPHParticle particle;
	IndexedFinder finder(1.0f);
	finder.add({ &particle });
	auto result = finder.find(particle.getPosition());
}