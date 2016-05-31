#include "gtest/gtest.h"

#include "../Polygon/Particle.h"

#include "../Math/Box3d.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(ParticleTest, TestGetBoundingBox)
{
	Particle particle(Vector3d<float>(0.0, 0.0, 0.0), 1.0f, 0.5f);
	Box3d<float> expected(Vector3d<float>(-0.5, -0.5, -0.5), Vector3d<float>(0.5, 0.5, 0.5));
	EXPECT_EQ(expected, particle.getBoundingBox());
}


TEST(ParticleTest, TestCreateBlended)
{
	Particle particle1(Vector3d<float>(0.0f, 0.0f, 0.0f), 0.0f, 0.5f);
	Particle particle2(Vector3d<float>(1.0f, 1.0f, 1.0f), 10.0f, 0.5f);
	const auto actual = particle1.createBlended(particle2, 0.8f);
	EXPECT_EQ( Vector3d<float>(0.8f, 0.8f, 0.8f), actual.getPosition());
	EXPECT_FLOAT_EQ( 8, actual.getDensity());
}