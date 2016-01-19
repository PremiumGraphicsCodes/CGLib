#include "gtest/gtest.h"

#include "../Math/Grid1d.h"

using namespace Crystal::Math;

TEST(Grid1dTest, TestGetSize)
{
	using T = float;
	EXPECT_EQ(2, Grid1d<T>(2).getSize());
	EXPECT_EQ(10, Grid1d<T>(10).getSize());
}

TEST(Grid1dTest, TestGet)
{
	using T = float;
	EXPECT_EQ(0, Grid1d<T>(2, 0).get(0));
}

TEST(Grid1dTest, TestSet)
{
	using T = float;
	Grid1d<T> grid(2, 10);
	grid.set(1, Grid1d<T>(1, 20));
	EXPECT_EQ(20, grid.get(1));
}

TEST(Grid1dTest, TestGetSub)
{
	using T = float;
	EXPECT_EQ(Grid1d<T>(1, 0), Grid1d<T>(2, 0).getSub(0, 1));
	EXPECT_EQ(Grid1d<T>(2, 100), Grid1d<T>(5, 100).getSub(0, 2));
}

TEST(Grid1dTest, TestIsValidIndex)
{
	using T = float;
	EXPECT_FALSE(Grid1d<T>(2).isValidIndex(-1));
	EXPECT_TRUE( Grid1d<T>(2).isValidIndex(0) );
	EXPECT_TRUE( Grid1d<T>(2).isValidIndex(1));
	EXPECT_FALSE(Grid1d<T>(2).isValidIndex(2));

}
