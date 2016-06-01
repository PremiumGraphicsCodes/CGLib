#include "gtest\gtest.h"

#include "../Math/Ellipsoid.h"

using namespace Crystal::Math;

TEST(EllipsoidTest, TestGetVolume)
{
	using T = float;
	{
		Ellipsoid<float> e(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 1, 1));
		const auto expected = Angle<float>::getPI() * T{ 4 } / T{ 3 };
		EXPECT_FLOAT_EQ(expected, e.getVolume());
	}
	{
		Ellipsoid<float> e(Vector3d<float>(0, 0, 0), Vector3d<float>(2, 1, 1));
		const auto expected = Angle<float>::getPI() * T { 4 } / T{ 3 } *T{ 2 };
		EXPECT_FLOAT_EQ(expected, e.getVolume());
	}

}