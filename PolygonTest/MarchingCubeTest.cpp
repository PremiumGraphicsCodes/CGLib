#include "gtest/gtest.h"

#include "../Polygon/MarchingCube.h"
#include "../Math/Volume3d.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

/*
TEST(MarchingCubeTest, TestMarchScalarSpace)
{
	MarchingCube mc;

	Space3d<float> s(Vector3d<float> (0, 0, 0), Vector3d<float>(10, 10, 10));
	Grid3d<float> grid(4, 4, 4);
	grid.set(0, 0, 0, 0.8f);
	grid.set(1, 0, 0, 0.8f);
	Volume3d<float, float> ss(s, grid);

	//mc.march(ss, 0.5);
}
*/

TEST(MCGridTest, Test)
{
	Space3d<float> space(Vector3d<float>(0, 0, 0), Vector3d<float>(2,2,2));
	Grid3d<float> grid(2, 2, 2);
	grid.set(0, 0, 0, 1);

	Volume3d<float, float> volume(space, grid);
	MCGrid mcgrid(volume, 0.5);
}