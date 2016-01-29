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
	Space3d<float> space(Vector3d<float>(0, 0, 0), Vector3d<float>(4,4,4));
	Grid3d<float> grid(4, 4, 4);
	grid.set(0, 0, 0, 1);

	MCGrid mcgrid(0.5);
	{
		Volume3d<float, float> volume(space, grid);
		mcgrid.march(volume);
		const auto& actual = mcgrid.getVertices();
		EXPECT_EQ(3, actual.size());
		EXPECT_EQ(Vector3d<float>(1.0, 0.5, 0.5), actual[0]->getPosition());
		EXPECT_EQ(Vector3d<float>(0.5, 1.0, 0.5), actual[1]->getPosition());
		EXPECT_EQ(Vector3d<float>(0.5, 0.5, 1.0), actual[2]->getPosition());
	}
	mcgrid.clear();

	grid.set(1, 0, 0, 1);
	{
		Volume3d<float, float> volume(space, grid);
		mcgrid.march(volume);
		const auto& actual = mcgrid.getVertices();
		EXPECT_EQ(5, actual.size());

	}

	/*
	grid.set(0, 1, 0, 1);
	{
		Volume3d<float, float> volume(space, grid);
		MCGrid mcgrid(volume, 0.5);
		const auto& actual = mcgrid.getVertices();
		EXPECT_EQ(5, actual.size());
	}
	*/
}