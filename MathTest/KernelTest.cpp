#include "gtest/gtest.h"

#include "../Math/Kernel.h"

using namespace Crystal::Math;

TEST(Kernel1dTest, TestGet)
{
	using T = float;
	Gaussian<T> k;
	const auto expected = T(1) / std::sqrt(T(2) * Tolerance<T>::getPI());
	EXPECT_FLOAT_EQ(expected, k.get(0) );
	EXPECT_FLOAT_EQ(expected*2, k.get(0,0));
	EXPECT_FLOAT_EQ(expected * 3, k.get(0,0,0));

	EXPECT_FLOAT_EQ( k.get(2), k.get(-2) );

}
