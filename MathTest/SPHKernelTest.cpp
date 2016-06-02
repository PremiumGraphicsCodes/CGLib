#include "gtest\gtest.h"

#include "../Math/SPHKernel.h"

using namespace Crystal::Math;

TEST(SPHKernelTest, TestGetCubicSpiline)
{
	SPHKernel<float> kernel;
	{
		const auto actual = kernel.getCubicSpline(0);
		const auto expected = 1.0f / Tolerance<float>::getPI();
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}
	{
		const auto actual = kernel.getCubicSpline(1);
		const auto expected = 1.0f / (4 * Tolerance<float>::getPI());
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}
	{
		const auto actual = kernel.getCubicSpline(2);
		const auto expected = 0.0f;
		EXPECT_TRUE(Tolerance<float>::isEqualLoosely(expected, actual));
	}

}