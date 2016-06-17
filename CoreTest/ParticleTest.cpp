#include "stdafx.h"

#include "../Core/Particle.h"

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

TEST(ParticleTest, TestGetMatrix)
{
	{
		Particle particle(Vector3d<float>(0.0, 0.0, 0.0), 1.0f, 0.5f);
		const Matrix3d<float> expected(0.5, 0, 0, 0, 0.5, 0, 0, 0, 0.5);
		const auto& actual = particle.getMatrix();
		EXPECT_EQ(expected, actual);
	}
	{
		Particle particle(Vector3d<float>(0.0, 0.0, 0.0), 1.0f, 5.0f);
		const Matrix3d<float> expected(5.0, 0, 0, 0, 5.0, 0, 0, 0, 5.0);
		const auto& actual = particle.getMatrix();
		EXPECT_EQ(expected, actual);

	}
}
