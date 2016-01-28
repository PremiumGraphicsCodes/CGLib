#include "gtest/gtest.h"

#include "../Graphics/MarchingCube.h"
#include "../Math/Volume3d.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;


TEST(MarchingCubeTest, TestMarchScalarSpace)
{
	MarchingCube mc;

	Space3d<float> s(Vector3d<float> (0, 0, 0), Vector3d<float>(10, 10, 10));
	Grid3d<float> grid(4, 4, 4);
	grid.set(0, 0, 0, 0.8);
	grid.set(1, 0, 0, 0.8);
	Volume3d<float, float> ss(s, grid);

	mc.march(ss, 0.5);
}