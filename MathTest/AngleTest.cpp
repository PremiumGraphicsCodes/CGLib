#include "gtest\gtest.h"

#include "../Math/Angle.h"
#include "../Math/Tolerance.h"

using namespace Crystal::Math;

using T = double;

TEST(RadianTest, TestToDegree)
{
	{
		Radian<T> rad(0.0 * Tolerance<T>::getPI());
		EXPECT_EQ(Degree<T>(0), rad.toDegree());
	}

	{
		Radian<T> rad(Tolerance<T>::getPI());
		EXPECT_EQ(Degree<T>(180), rad.toDegree());
	}
	{
		Radian<T> rad(T{ 2 } *Tolerance<T>::getPI());
		EXPECT_EQ(Degree<T>(360), rad.toDegree());
	}
}