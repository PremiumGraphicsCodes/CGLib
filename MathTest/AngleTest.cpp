#include "gtest\gtest.h"

#include "../Math/Angle.h"
#include "../Math/Tolerance.h"

using namespace Crystal::Math;

using T = double;

TEST(RadianTest, TestToDegree)
{
	EXPECT_EQ(Degree<T>(0), Radian<T>(0.0 * Tolerance<T>::getPI()).toDegree());
	EXPECT_EQ(Degree<T>(180), Radian<T>(Tolerance<T>::getPI()).toDegree());
	EXPECT_EQ(Degree<T>(360), Radian<T>(T{ 2 } *Tolerance<T>::getPI()).toDegree());
}

TEST(DegreeTest, TestToRadian)
{
	EXPECT_EQ(Radian<T>(0.0 * Tolerance<T>::getPI()), Degree<T>(0).toRadian());

	/*
	{
		Radian<T> rad(Tolerance<T>::getPI());
		EXPECT_EQ(Degree<T>(180), rad.toDegree());
	}
	{
		Radian<T> rad(T{ 2 } *Tolerance<T>::getPI());
		EXPECT_EQ(Degree<T>(360), rad.toDegree());
	}
	*/
}