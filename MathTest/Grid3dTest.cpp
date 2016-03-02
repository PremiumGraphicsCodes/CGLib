#include "gtest/gtest.h"

#include "../Math/Grid3d.h"
#include "../Math/Vector3d.h"

using namespace Crystal::Math;

TEST(Grid3dTest, TestToArray8)
{
	using T = float;
	std::array<T, 8> expected{ 0, 0, 0, 0, 0, 0, 0, 0 };
	EXPECT_EQ( expected, Grid3d<T>(2, 2, 2, 0).toArray8(0,0,0));
}

TEST(Grid3dTest, TestAdd)
{
	using T = float;
	auto lhs = Grid3d<T>(2, 2, 2, 0);
	lhs.set(0, 0, 0, 20);
	auto rhs = Grid3d<T>(2, 2, 2, 0);
	rhs.set(1, 1, 1, 10);
	lhs.add(rhs, { 0,0,0 });

	auto expected = Grid3d<T>(2, 2, 2, 0);
	expected.set(0, 0, 0, 20);
	expected.set(1, 1, 1, 10);
	EXPECT_EQ(expected, lhs);
}

TEST(Grid3dTest, TestSubGrid)
{
	using T = float;
	Grid3d<T> grid(2, 2, 2, 0);
	grid.set(0, 1, 0, 20);
	const auto& actual = grid.subGrid(Index3d(0, 1, 0), Index3d(2,2,2));

	Grid3d<T> expected(2, 1, 2, 0);
	expected.set(0, 0, 0, 20);
	EXPECT_EQ(expected, actual);
}

TEST(Grid3dTest, TestSub)
{
	using T = float;
	auto lhs = Grid3d<T>(2, 2, 2, 0);
	lhs.set(0, 0, 0, 20);
	auto rhs = Grid3d<T>(2, 2, 2, 0);
	rhs.set(1, 1, 1, -10);
	lhs.add(rhs, { 0,0,0 });

	auto expected = Grid3d<T>(2, 2, 2, 0);
	expected.set(0, 0, 0, 20);
	expected.set(1, 1, 1, -10);
	EXPECT_EQ(expected, lhs);
}

TEST(Grid3dTest, TestIsLower)
{
	using T = float;
	Grid3d<T> grid(2, 2, 2, 0);
	grid.set(0, 0, 0, 10);
	const T threshold = 5;
	EXPECT_FALSE(grid.isLower(0, 0, 0, threshold));
	EXPECT_TRUE( grid.isLower(1, 0, 0, threshold));
}

TEST(Grid3dTest, TestIsAllLower)
{
	using T = float;
	Grid3d<T> grid(2, 2, 2, 0);
	const T threshold = 5;

	EXPECT_TRUE(  grid.isAllLower(0, 0, 0, threshold) );
	grid.set(0, 0, 0, 10);
	EXPECT_FALSE( grid.isAllLower(0, 0, 0, threshold) );
}

TEST(Grid3dTest, TestIsAllHigher)
{
	using T = float;
	Grid3d<T> grid(2, 2, 2, 0);
	const T threshold = 5;

	EXPECT_FALSE(grid.isAllHigher(0, 0, 0, threshold));
	grid.set(0, 0, 0, 10);
	EXPECT_FALSE(grid.isAllHigher(0, 0, 0, threshold));
}

TEST(Grid3dTest, TestIsBoundary)
{
	using T = float;
	Grid3d<T> grid(2, 2, 2, 0);
	const T threshold = 5;

	EXPECT_FALSE( grid.isBoundary(0, 0, 0, threshold) );
	grid.set(0, 0, 0, 10);
	EXPECT_TRUE(  grid.isBoundary(0, 0, 0, threshold) );
}

TEST(Grid3dTest, TestIsValidIndex)
{
	using T = float;
	Grid3d<T> grid(1, 2, 4, 0);
	EXPECT_TRUE( grid.isValidIndex(0, 0, 0) );
	EXPECT_FALSE(grid.isValidIndex(1, 0, 0) );
	EXPECT_TRUE(grid.isValidIndex(0, 1, 0) );
}

TEST(Grid3dTest, TestGetLocalCoord)
{
	using T = float;
	Grid3d<T> grid(1, 2, 4, 0);
	const auto actual = grid.getLocalCoord({ 0,0,0 });
	EXPECT_EQ(Vector3d<T>(-0.5, -0.5, -0.5), actual);
}

TEST(Grid3dTest, TestCreateRotateX)
{
	using T = float;
	Grid3d<T> grid(2, 2, 2, 0);
	grid.set(0, 0, 0, 0);
	grid.set(1, 0, 0, 100);
	grid.set(0, 1, 0, 10);
	grid.set(0, 0, 1, 1);

	const auto& actual = grid.createRotateX();
	EXPECT_EQ(0, actual.get(0, 0, 0));
	EXPECT_EQ(10, actual.get(0, 0, 1));
	EXPECT_EQ(1, actual.get(0, 1, 0));
}

TEST(Grid3dTest, TestCreateRotateY)
{
	using T = float;
	Grid3d<T> grid(2, 2, 2, 0);
	grid.set(0, 0, 0, 0);
	grid.set(1, 0, 0, 100);
	grid.set(0, 1, 0, 10);
	grid.set(0, 0, 1, 1);

	const auto& actual = grid.createRotateY();
	EXPECT_EQ(0, actual.get(0, 0, 0));
	EXPECT_EQ(100, actual.get(0, 0, 1));
	EXPECT_EQ(10, actual.get(0, 1, 0));
	EXPECT_EQ(1, actual.get(1, 0, 0));
	//EXPECT_EQ(1, actual.get(0, 1, 0));
}

TEST(Grid3dTest, TestCreateRotateZ)
{
	using T = float;
	Grid3d<T> grid(2, 2, 2, 0);
	grid.set(0, 0, 0, 0);
	grid.set(1, 0, 0, 100);
	grid.set(0, 1, 0, 10);
	grid.set(0, 0, 1, 1);

	const auto& actual = grid.createRotateZ();
	EXPECT_EQ(0, actual.get(0, 0, 0));
	EXPECT_EQ(1, actual.get(0, 0, 1));
}