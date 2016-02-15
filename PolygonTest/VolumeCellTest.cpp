#include "gtest\gtest.h"

#include "../Polygon/VolumeCell.h"

#include "../Math/Triangle.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

TEST(VolumeCellTest, TestToTriangle)
{
	Space3d<float> space;
	std::array<float, 8> values;
	VolumeCell cell(space, values);
	const auto actual = cell.toTriangles(0.5f);
	EXPECT_EQ(0, actual.size());
}