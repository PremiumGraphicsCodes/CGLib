#include "gtest\gtest.h"

#include "../Core/VolumeCell.h"

#include "../Math/Triangle.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(VolumeCellTest, TestToTrianglePattern0)
{
	Space3d<float> space;
	std::array<float, 8> values = { 0.0f, 0.0f ,0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, };
	VolumeCell cell(space, values);
	const auto actual = cell.toTriangles(0.5f);
	EXPECT_EQ(0, actual.size());
}

TEST(VolumeCellTest, TestToTrianglePattern1)
{
	Space3d<float> space;
	std::array<float, 8> values = { 1.0f, 0.0f ,0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, };
	VolumeCell cell(space, values);
	const auto actual = cell.toTriangles(0.5f);
	EXPECT_EQ(1, actual.size());
}

TEST(VolumeCellTest, TestToTrianglePattern2)
{
	Space3d<float> space;
	std::array<float, 8> values = { 1.0f, 1.0f ,0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, };
	VolumeCell cell(space, values);
	const auto actual = cell.toTriangles(0.5f);
	EXPECT_EQ(2, actual.size());
}

TEST(VolumeCellTest, TestToTrianglePattern3)
{
	Space3d<float> space;
	std::array<float, 8> values = { 1.0f, 0.0f ,1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, };
	VolumeCell cell(space, values);
	const auto actual = cell.toTriangles(0.5f);
	EXPECT_EQ(4, actual.size());
}

TEST(VolumeCellTest, TestToTrianglePattern4)
{
	Space3d<float> space;
	std::array<float, 8> values = { 1.0f, 0.0f ,0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, };
	VolumeCell cell(space, values);
	const auto actual = cell.toTriangles(0.5f);
	EXPECT_EQ(2, actual.size());
}