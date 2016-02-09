#include "gtest/gtest.h"

#include "../Polygon/Particle.h"

#include "../Math/Box.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

TEST(ParticleTest, TestGetBoundingBox)
{
	Particle particle(Vector3d<float>(0.0, 0.0, 0.0), 1.0f, 0.5f);
	Box<float> expected(Vector3d<float>(-0.5, -0.5, -0.5), Vector3d<float>(0.5, 0.5, 0.5));
	EXPECT_EQ(expected, particle.getBoundingBox());
}


TEST(ParticleTest, TestCreateBlended)
{
	Particle particle1(Vector3d<float>(0.0, 0.0, 0.0), 0.0f, 0.5f);
	Particle particle2(Vector3d<float>(1.0, 1.0, 1.0), 10.0f, 0.5f);
	const auto actual = particle1.createBlended(particle2, 0.8);
	EXPECT_FLOAT_EQ( 8, actual.getDensity());
}