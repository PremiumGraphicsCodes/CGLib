#include "gtest\gtest.h"
#include "../Math/Cone.h"

using namespace Crystal::Math;

TEST(ConeTest, TestGetVolume)
{
	Cone<float> cone(1, 1);
	EXPECT_FLOAT_EQ(Tolerance<float>::getPI() / 3.0f, cone.getVolume());
}

TEST(ConeTest, TestGetPositionByAngleAndParam)
{
	const Cone<float> cone(1, 1);
	EXPECT_EQ(Vector3d<float>(1,-0.5,0), cone.getPosition(Angle<float>::Zero(), Param<float>(0)));
	EXPECT_EQ(Vector3d<float>(-1, -0.5, 0), cone.getPosition(Angle<float>::PI(), Param<float>(0)));

	EXPECT_EQ(Vector3d<float>(0.5, 0, 0), cone.getPosition(Angle<float>::Zero(), Param<float>(0.5)));
	EXPECT_EQ(Vector3d<float>(-0.5, 0, 0), cone.getPosition(Angle<float>::PI(), Param<float>(0.5)));

	EXPECT_EQ(Vector3d<float>(0, 0.5,0), cone.getPosition(Angle<float>::Zero(), Param<float>(1)));
	EXPECT_EQ(Vector3d<float>(0, 0.5,0), cone.getPosition(Angle<float>::PI(), Param<float>(1)));
}

TEST(ConeTest, TestGetPositionByParamAndParam)
{
	{
		const Cone<float> cone(1, 1);
		EXPECT_EQ(Vector3d<float>(1, -0.5, 0), cone.getPosition(Param<float>(0), Param<float>(0)));
		EXPECT_EQ(Vector3d<float>(-1, -0.5, 0), cone.getPosition(Param<float>(0.5), Param<float>(0)));

		EXPECT_EQ(Vector3d<float>(0, 0.5, 0), cone.getPosition(Param<float>(0), Param<float>(1)));
		EXPECT_EQ(Vector3d<float>(0, 0.5, 0), cone.getPosition(Param<float>(1), Param<float>(1)));
	}

	{
		const Quaternion<float> q(Vector3d<float>(0, 1, 0), Tolerance<float>::getPI());
		const Cone<float> cone(1, 1, Vector3d<float>(0, 0, 0), q);
		EXPECT_EQ(Vector3d<float>(-1, -0.5, 0), cone.getPosition(Param<float>(0), Param<float>(0)));
		EXPECT_EQ(Vector3d<float>(1, -0.5, 0), cone.getPosition(Param<float>(0.5), Param<float>(0)));

//		EXPECT_EQ(Vector3d<float>(0, 0.5, 0), cone.getPosition(Param<float>(0), Param<float>(1)));
//		EXPECT_EQ(Vector3d<float>(0, 0.5, 0), cone.getPosition(Param<float>(1), Param<float>(1)));
	}
}

TEST(ConeTest, TestGetNormal)
{
	const Cone<float> cone(1, 1);
	EXPECT_EQ(Vector3d<float>(1, 2.0f/3.0f, 0).normalized(), cone.getNormal(Angle<float>::Zero(), Param<float>(0)));
	EXPECT_EQ(Vector3d<float>(-1, 2.0f/3.0f, 0).normalized(), cone.getNormal(Angle<float>::PI(), Param<float>(0)));
}