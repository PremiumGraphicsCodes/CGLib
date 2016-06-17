#include "stdafx.h"

#include "../Core/NodeGrid.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(NodeGridTest, Test)
{
	NodeGrid grid(2,2);
	Node n00(Vector3d<float>(0,0,0), 0);
	Node n01(Vector3d<float>(0,0,0),1);
	Node n10(Vector3d<float>(0,0,0), 2);
	Node n11(Vector3d<float>(0, 0, 0), 3);

	grid.set(0, 0, &n00);
	grid.set(0, 1, &n01);
	grid.set(1, 0, &n10);
	grid.set(1, 1, &n11);

	EXPECT_EQ(nullptr, grid.getPrevU(0, 0));

	EXPECT_EQ(&n01, grid.getNextU(0, 0));
	EXPECT_EQ(nullptr, grid.getNextU(0, 1));
	EXPECT_EQ(&n11, grid.getNextU(1, 0));
	EXPECT_EQ(nullptr, grid.getNextU(1, 1));

}