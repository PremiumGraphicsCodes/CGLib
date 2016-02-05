#include "gtest\gtest.h"

#include "../Polygon/SpaceHash.h"
#include "../Polygon/ParticleObject.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

TEST(SpaceHashTest, Test)
{
	SpaceHash hash(1.0f);
	Particle p1(Vector3d<float>(0.0f, 0.0f, 0.0f));
	Particle p2(Vector3d<float>(1.0f, 0.0f, 0.0f));
	Particle p3(Vector3d<float>(2.0f, 0.0f, 0.0f));
	hash.add(&p1);
	hash.add(&p2);
	hash.add(&p3);
	auto actual = hash.getNeighbor(&p1);
	EXPECT_EQ(2, actual.size());
	EXPECT_EQ(&p1, actual.back());
	EXPECT_EQ(&p2, actual.front());

}