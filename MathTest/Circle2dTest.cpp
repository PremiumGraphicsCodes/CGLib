#include "gtest\gtest.h"

#include "../Math/Circle2d.h"

using namespace Crystal::Math;

TEST(Circle2dTest, TestToPoints)
{
	Circle2d<float> c;
	const auto& actual = c.toCurve2d(3);

	EXPECT_EQ(3, actual.size());

	{
		Vector2d<float> position(::sin(0 * Tolerance<float>::getPI()), ::cos(0 * Tolerance<float>::getPI()));
		Vector2d<float> normal(0, 1);
		const float param = 0;
		Point2d<float> expected(position, normal, param);
		EXPECT_EQ(expected, actual[0]);

	}
	/*
	{
		const auto x = ::sin(120.0f / 180.0f * Tolerance<float>::getPI());
		const auto y = ::cos(120.0f / 180.0f * Tolerance<float>::getPI());

		Vector2d<float> expected(x, y);
		EXPECT_EQ( expected, actual[1] );
	}
	{
		const auto x = ::sin(240.0f / 180.0f * Tolerance<float>::getPI());
		const auto y = ::cos(240.0f / 180.0f * Tolerance<float>::getPI());
		Vector2d<float> expected(x, y);
		EXPECT_EQ(expected, actual[2]);
	}
	*/
}