#include "gtest/gtest.h"

#include "../Math/MarchingCubeTable.h"

using namespace Crystal::Math;

TEST(MarchingCubeTableTest, TestBuildEdgeTable)
{
	MarchingCubeTable table;
	table.buildEdgeTable();

	EXPECT_EQ(256,table.getEdgeTable().size());
}

TEST(MarchingCubeTableTest, TestBuildTriangleTable)
{
	MarchingCubeTable table;
	table.buildTriangleTable();

	EXPECT_EQ(256, table.getTriangleTable().size());

}