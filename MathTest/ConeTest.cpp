#include "gtest\gtest.h"
#include "../Math/Cone.h"

using namespace Crystal::Math;

TEST(ConeTest, TestGetVolume)
{
	Cone<float> cone(1, 1);
	EXPECT_FLOAT_EQ(Tolerance<float>::getPI() / 3.0, cone.getVolume());
}

TEST(ConeTest, TestGetPosition)
{
	Cone<float> cone(1, 1);
	EXPECT_EQ(Vector3d<float>(1,-0.5,0), cone.getPosition(Angle<float>::Zero(), Param<float>(0)));
	EXPECT_EQ(Vector3d<float>(-1, -0.5, 0), cone.getPosition(Angle<float>::PI(), Param<float>(0)));

	EXPECT_EQ(Vector3d<float>(0.5, 0, 0), cone.getPosition(Angle<float>::Zero(), Param<float>(0.5)));
	EXPECT_EQ(Vector3d<float>(-0.5, 0, 0), cone.getPosition(Angle<float>::PI(), Param<float>(0.5)));

	EXPECT_EQ(Vector3d<float>(0, 0.5,0), cone.getPosition(Angle<float>::Zero(), Param<float>(1)));
	EXPECT_EQ(Vector3d<float>(0, 0.5,0), cone.getPosition(Angle<float>::PI(), Param<float>(1)));
}

TEST(ConeTest, TestGetNormal)
{
	Cone<float> cone(1, 1);
	EXPECT_EQ(Vector3d<float>(1, 2.0f/3.0f, 0).getNormalized(), cone.getNormal(Angle<float>::Zero(), Param<float>(0)));
	EXPECT_EQ(Vector3d<float>(-1, 2.0f/3.0f, 0).getNormalized(), cone.getNormal(Angle<float>::PI(), Param<float>(0)));
}