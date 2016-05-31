#include "gtest/gtest.h"

#include "../Polygon/VolumeObject.h"
#include "../Polygon/MarchingCube.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

TEST(PositionValueTest, TestInterpolate)
{
	VolumeNode pv1(Vector3d<float>(0, 0, 0), 0);
	VolumeNode pv2(Vector3d<float>(2, 4, 6), 10);
	const auto& actual = pv1.getInterpolatedPosition(5, pv2);
	const Vector3d<float> expected(1, 2, 3);
	EXPECT_EQ(expected, actual);
}

/*
TEST(VolumeCell3dTest, TestToPositionValues)
{

	const Space3d<float> space(Vector3d<float>(0, 0, 0), Vector3d<float>(10, 20, 30));
	const std::array < float, 8 > values = { 0, 1, 2, 3, 4, 5, 6, 7 };
	const VolumeCell3d cell(space, values);
	const auto& actual = cell.toPositionValues();
	const auto expected = PositionValue(Vector3d<float>(0, 0, 0), 0);
	EXPECT_EQ(expected, actual[0]);
}
*/

TEST(MCGridTest, Test)
{
	Space3d<float> space(Vector3d<float>(0, 0, 0), Vector3d<float>(4,4,4));
	Grid3d<float> grid(4, 4, 4);
	grid.set(1, 0, 0, 1);

	MarchingCube mc;
	{
		const auto& actual = mc.march(space, grid,  0.5);
		EXPECT_EQ(2, actual.size());
		//EXPECT_EQ(Vector3d<float>(1.0, 0.5, 0.5), actual[0]->getPosition());
		//EXPECT_EQ(Vector3d<float>(0.5, 1.0, 0.5), actual[1]->getPosition());
		//EXPECT_EQ(Vector3d<float>(0.5, 0.5, 1.0), actual[2]->getPosition());
	}
}