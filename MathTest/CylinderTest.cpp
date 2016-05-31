#include "gtest\gtest.h"
#include "../Math/Cylinder.h"
#include "../Math/Tolerance.h"

using namespace Crystal::Math;

TEST(CylinderTest, TestGetVolume)
{
	Cylinder<float> cylinder(1.0, 1.0 );
	EXPECT_EQ( Tolerance<float>::getPI(), cylinder.getVolume() );
}