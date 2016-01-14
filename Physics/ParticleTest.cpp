#include "gtest/gtest.h"

#include "../Physics/Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Physics;

using T = float;

TEST(ParticleConstantTest, TestConstruct)
{
	Particle<T>::Constant constant;
	EXPECT_EQ(1.0f, constant.getDiameter() );
	EXPECT_EQ(1.0f, constant.getRestDensity());
}


TEST(ParticleConstantTest, TestGetVolume)
{
	Particle<T>::Constant constant;
	constant.diameter = 2.0f;
	EXPECT_FLOAT_EQ(8.0f, constant.getVolume());
}

TEST(ParticleTest, TestConstruct)
{
	const Particle<T> particle;
	EXPECT_EQ(Vector3d<T>(0.0f, 0.0f, 0.0f), particle.getCenter());
}

TEST(ParticleTest, TestConstructByPosition)
{
	const Particle<T> particle(Vector3d<T>(1.0f, 2.0f, 3.0f));
	EXPECT_EQ(Vector3d<T>(1.0f, 2.0f, 3.0f), particle.getCenter());
}

TEST(ParticleTest, TestConstructByConstant)
{
	const Particle<T>::Constant constant;
	const Particle<T> particle(constant, Vector3d<T>( 0.0f, 0.0f, 0.0f ) );
}
