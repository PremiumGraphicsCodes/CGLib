#include "stdafx.h"

#include "../Core/NodeGrid.h"
#include "../Core/Vertex.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(NodeGridTest, Test)
{
	NodeGrid grid(2,2);
	Vertex n00(Vector3d<float>(0,0,0), 0);
	Vertex n01(Vector3d<float>(0,0,0),1);
	Vertex n10(Vector3d<float>(0,0,0), 2);
	Vertex n11(Vector3d<float>(0, 0, 0), 3);

	grid.set(0, 0, &n00);
	grid.set(0, 1, &n01);
	grid.set(1, 0, &n10);
	grid.set(1, 1, &n11);

	EXPECT_EQ(&n00, grid.get(0, 0));
	EXPECT_EQ(&n01, grid.get(0, 1));
	EXPECT_EQ(&n10, grid.get(1, 0));
	EXPECT_EQ(&n11, grid.get(1, 1));


	EXPECT_EQ(nullptr, grid.getPrevU(0, 0));

	EXPECT_EQ(&n01, grid.getNextU(0, 0));
	EXPECT_EQ(nullptr, grid.getNextU(0, 1));
	EXPECT_EQ(&n11, grid.getNextU(1, 0));
	EXPECT_EQ(nullptr, grid.getNextU(1, 1));
	EXPECT_EQ(nullptr, grid.getPrevU(0, 0));
	EXPECT_EQ(&n00, grid.getPrevU(0, 1));

	EXPECT_EQ(nullptr, grid.getPrevU(0, 0));

	EXPECT_EQ(nullptr, grid.getPrevV(0, 0));


	EXPECT_EQ(&n10, grid.getNextV(0, 0));
	EXPECT_EQ(&n11, grid.getNextV(0, 1));

	const auto& cells = grid.toQuadCells();
	EXPECT_EQ(1, cells.size());
}

TEST(NodeGrid1dTest, Test)
{
	NodeGrid1d grid(2, 2);
	Vertex n00(Vector3d<float>(0, 0, 0), 0);
	Vertex n01(Vector3d<float>(0, 0, 0), 1);
	Vertex n10(Vector3d<float>(0, 0, 0), 2);
	Vertex n11(Vector3d<float>(0, 0, 0), 3);

	grid.set(0, 0, &n00);
	grid.set(0, 1, &n01);
	grid.set(1, 0, &n10);
	grid.set(1, 1, &n11);


	EXPECT_EQ(&n01, grid.getNextU(0, 0));
	EXPECT_EQ(&n00, grid.getNextU(0, 1));
	EXPECT_EQ(&n01, grid.getPrevU(0, 0));
	EXPECT_EQ(&n00, grid.getPrevU(0, 1));

	const auto& cells = grid.toQuadCells();
	EXPECT_EQ(1, cells.size());
}

TEST(NodeGrid2dTest, Test)
{
	NodeGrid2d grid(2, 2);
	Vertex n00(Vector3d<float>(0, 0, 0), 0);
	Vertex n01(Vector3d<float>(0, 0, 0), 1);
	Vertex n10(Vector3d<float>(0, 0, 0), 2);
	Vertex n11(Vector3d<float>(0, 0, 0), 3);

	grid.set(0, 0, &n00);
	grid.set(0, 1, &n01);
	grid.set(1, 0, &n10);
	grid.set(1, 1, &n11);


	EXPECT_EQ(&n01, grid.getNextV(1, 1));
	EXPECT_EQ(&n11, grid.getNextV(0, 1));
	EXPECT_EQ(&n00, grid.getNextV(1, 0));

	//EXPECT_EQ(&n00, grid.getNextU(0, 1));
	//EXPECT_EQ(&n01, grid.getPrevU(0, 0));
	//EXPECT_EQ(&n00, grid.getPrevU(0, 1));

}