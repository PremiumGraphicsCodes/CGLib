#include "gtest\gtest.h"

#include "../Math/Ellipsoid.h"
#include "../Math/Curve3d.h"

using namespace Crystal::Math;

TEST(EllipsoidTest, TestGetVolume)
{
	using T = float;
	{
		Ellipsoid<float> e(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 1, 1));
		const auto expected = Tolerance<float>::getPI() * T{ 4 } / T{ 3 };
		EXPECT_FLOAT_EQ(expected, e.getVolume());
	}
	{
		Ellipsoid<float> e(Vector3d<float>(0, 0, 0), Vector3d<float>(2, 1, 1));
		const auto expected = Tolerance<float>::getPI() * T { 4 } / T{ 3 } *T{ 2 };
		EXPECT_FLOAT_EQ(expected, e.getVolume());
	}
}

TEST(EllipsoidTest, TestGetPosition)
{
	using T = float;
	Ellipsoid<T> e(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 1, 1));

	{
		const auto& actual = e.getPosition(Angle<T>(Degree<T>(0)), Angle<T>(Degree<T>(0)));
		Vector3d<float> expected(1, 0, 0);
		EXPECT_EQ(expected, actual);
	}


	{
		const auto& actual = e.getPosition(Angle<T>(Degree<T>(180)), Angle<T>(Degree<T>(0)));
		Vector3d<float> expected(-1, 0, 0);
		EXPECT_EQ(expected, actual);
	}

	{
		const auto& actual = e.getPosition(Angle<T>(Degree<T>(0)), Angle<T>(Degree<T>(90)));
		Vector3d<float> expected(0, 0, 1);
		EXPECT_EQ(expected, actual);
	}
}

TEST(EllipsoidTest, TestToCurve3d)
{
	using T = float;
	{
		Ellipsoid<float> e(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 1, 1));
		const auto& actual = e.toCurve3d(2, 2);
	}
}