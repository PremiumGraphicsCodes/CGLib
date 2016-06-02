#include "gtest\gtest.h"

#include "../Core/AnisotoropicParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(AnisotoropicParticleTest, TestGetMatrix)
{
	AnisotoropicParticle particle;
	const auto& actual = particle.getMatrix();
	const Matrix3d<float> expected(0.5, 0, 0, 0, 0.5, 0, 0, 0, 0.5);
	EXPECT_EQ(expected, actual);
}

TEST(AnisotoropicParticleTest, TestGetBoundingBox)
{
	{
		const AnisotoropicParticle particle;
		const auto& actual = particle.getBoundingBox();
		const Box3d<float> expected(Vector3d<float>(-0.5, -0.5, -0.5), Vector3d<float>(0.5, 0.5, 0.5));
		EXPECT_EQ(expected, actual);
	}

	{
		const Ellipsoid<float> e(Vector3d<float>(0, 0, 0), Vector3d<float>(2, 1, 1));
		const AnisotoropicParticle particle(e,1);
		const auto& actual = particle.getBoundingBox();
		const Box3d<float> expected(Vector3d<float>(-2, -1, -1), Vector3d<float>(2, 1, 1));
		EXPECT_EQ(expected, actual);
	}

}