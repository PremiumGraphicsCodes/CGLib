#include "stdafx.h"

#include "../Core/NodeCollection.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(NodeCollectionTest, Test)
{
	NodeCollection nodes;
	nodes.create(Point3d<float>(Vector3d<float>(1,2,3)));
	EXPECT_EQ(1, nodes.get().size());
}