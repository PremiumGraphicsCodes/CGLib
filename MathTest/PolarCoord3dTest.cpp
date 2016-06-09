#include "gtest\gtest.h"
#include "../Math/PolarCoord3d.h"

using namespace Crystal::Math;

TEST(PolarCoord3dTest, TestConstruct)
{
	{
		PolarCoord3d<float> polar(Vector3d<float>(0, 0, 1));
		PolarCoord3d<float> expected(1, Angle<float>(Degree<float>(0)), Angle<float>(Degree<float>(0)));
		EXPECT_EQ(polar, expected);
	}
	/*
	{
		PolarCoord3d<float> polar(Vector3d<float>(0, 0, 1));
		PolarCoord3d<float> expected(1, Angle<float>(Degree<float>(0)), Angle<float>(Degree<float>(90)));
		EXPECT_EQ(polar, expected);
	}
	*/
	{
		PolarCoord3d<float> polar(Vector3d<float>(0, 1, 0));
		PolarCoord3d<float> expected(1, Angle<float>(Degree<float>(90)), Angle<float>(Degree<float>(90)));
		EXPECT_EQ(polar, expected);
	}
}

TEST(PolarCoord3dTest, TestToOrtho)
{
	{
		PolarCoord3d<float> polar(1, Angle<float>(Degree<float>(180)), Angle<float>(Degree<float>(180)));
		const auto& actual = polar.toOrtho();
		const Vector3d<float> expected(0.0f, 0.0f, -1.0f);
		EXPECT_EQ(expected, actual);
	}

	{
		PolarCoord3d<float> polar(1, Angle<float>(Degree<float>(0)), Angle<float>(Degree<float>(0)));
		const auto& actual = polar.toOrtho();
		const Vector3d<float> expected(0.0f, 0.0f, 1.0f);
		EXPECT_EQ(expected, actual);
	}

	{
		PolarCoord3d<float> polar(1, Angle<float>(Degree<float>(0)), Angle<float>(Degree<float>(90)));
		const auto& actual = polar.toOrtho();
		const Vector3d<float> expected(0.0f, 0.0f, 1.0f);
		EXPECT_EQ(expected, actual);
	}

	{
		PolarCoord3d<float> polar(1, Angle<float>(Degree<float>(90)), Angle<float>(Degree<float>(0)));
		const auto& actual = polar.toOrtho();
		const Vector3d<float> expected(1.0f, 0.0f, 0.0f);
		EXPECT_EQ(expected, actual);
	}


	{
		PolarCoord3d<float> polar(1, Angle<float>(Degree<float>(90)), Angle<float>(Degree<float>(90)));
		const auto& actual = polar.toOrtho();
		const Vector3d<float> expected(0.0f, 1.0f, 0.0f);
		EXPECT_EQ(expected, actual);
	}
}

TEST(PolarCoord3dTest, TestToQuaternion)
{
	{
		PolarCoord3d<float> polar(1, Angle<float>(Degree<float>(0)), Angle<float>(Degree<float>(0)));
		const auto& actual = polar.toQuaternion();
		Quaternion<float> expected(0, 0, 0, 1);
		EXPECT_EQ(expected, actual);
	}

	{
		PolarCoord3d<float> polar(1, Angle<float>(Degree<float>(90)), Angle<float>(Degree<float>(90)));
		const auto& actual = polar.toQuaternion();
		Quaternion<float> expected(0.5, 0.5, 0.5, 0.5);
		EXPECT_EQ(expected, actual);
	}

	{
		PolarCoord3d<float> polar(1, Angle<float>(Degree<float>(90)), Angle<float>(Degree<float>(0)));
		const auto& actual = polar.toQuaternion();
		Quaternion<float> expected(Vector3d<float>(1,0,0), Tolerance<float>::getHalfPI());
		EXPECT_EQ(expected, actual);
	}
}