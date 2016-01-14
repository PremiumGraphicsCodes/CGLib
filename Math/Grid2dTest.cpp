#include "gtest/gtest.h"

#include "../Math/Grid2d.h"

using namespace Crystal::Math;


TEST(Grid2dTest, TestGetSizeX)
{
	using T = float;
	EXPECT_EQ(1, Grid2d<T>(1, 1).getSizeX());
	EXPECT_EQ(1, Grid2d<T>(1, 2).getSizeX());
	EXPECT_EQ(2, Grid2d<T>(2, 1).getSizeX());
	EXPECT_EQ(2, Grid2d<T>(2, 2).getSizeX());
}

TEST(Grid2dTest, TestGetSizeY)
{
	using T = float;
	EXPECT_EQ(1, Grid2d<T>(1, 1).getSizeY());
	EXPECT_EQ(2, Grid2d<T>(1, 2).getSizeY());
	EXPECT_EQ(1, Grid2d<T>(2, 1).getSizeY());
	EXPECT_EQ(2, Grid2d<T>(2, 2).getSizeY());
}

TEST(Grid2dTest, TestGetSub)
{
	using T = float;
	EXPECT_EQ(Grid2d<T>(1, 1), Grid2d<T>(2, 2).getSub(0, 1, 0, 1));
}
