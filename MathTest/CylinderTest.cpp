#include "gtest\gtest.h"
#include "../Math/Cylinder.h"
#include "../Math/Tolerance.h"
#include "../Math/Curve3d.h"

using namespace Crystal::Math;

TEST(CylinderTest, TestGetVolume)
{
	Cylinder<float> cylinder(Vector3d<float>(0,0,0), 1.0, 1.0 );
	EXPECT_EQ( Tolerance<float>::getPI(), cylinder.getVolume() );
}

TEST(CylinderTest, TestGetPosition)
{
	Cylinder<float> cylinder(Vector3d<float>(0, 0, 0), 1.0, 1.0);
	{
		const auto pos = cylinder.getPosition(Param<float>(0), Param<float>(0));
		EXPECT_EQ(Vector3d<float>(1, -0.5, 0), pos);
	}
	{
		const auto pos = cylinder.getPosition(Param<float>(0), Param<float>(1));
		EXPECT_EQ(Vector3d<float>(1, 0.5, 0), pos);
	}
}

TEST(CylinderTest, TestGetNormal)
{
	Cylinder<float> cylinder(Vector3d<float>(0, 0, 0), 1.0, 1.0);
	{
		const auto normal = cylinder.getNormal(Param<float>(0), Param<float>(0));
		EXPECT_EQ(Vector3d<float>(1, 0, 0), normal);
	}
	{
		const auto normal = cylinder.getNormal(Param<float>(0.5), Param<float>(0));
		EXPECT_EQ(Vector3d<float>(-1, 0, 0), normal);
	}
}

TEST(CylinderTest, TestToCurve3ds)
{
	Cylinder<float> cylinder(Vector3d<float>(0, 0, 0), 1.0, 1.0);
	{
		const auto curves = cylinder.toCurve3ds(2);
	}
}