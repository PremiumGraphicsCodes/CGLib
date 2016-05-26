#include "gtest\gtest.h"

#include "../Math/Circle.h"

using namespace Crystal::Math;

TEST(CircleTest, TestToPoints)
{
	Circle<float> c;
	const auto& actual = c.toPoints(3);
	EXPECT_EQ(3, actual.size());

	{
		Vector2d<float> expected(::sin(0 * Tolerance<float>::getPI()), ::cos(0 * Tolerance<float>::getPI()));
		EXPECT_EQ(expected, actual[0]);

	}
	{
		Vector2d<float> expected(::sin(120.0 / 180.0 * Tolerance<float>::getPI()), ::cos(120.0 / 180.0 * Tolerance<float>::getPI()));
		EXPECT_EQ( expected, actual[1] );
	}
}