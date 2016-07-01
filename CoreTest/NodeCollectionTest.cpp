#include "stdafx.h"

#include "../Core/NodeCollection.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(NodeCollectionTest, TestCreate)
{
	NodeCollection nodes;
	nodes.create(Point3d<float>(Vector3d<float>(1,2,3)));
	EXPECT_EQ(1, nodes.get().size());
}

TEST(NodeCollectionTest, TestMerge)
{
	NodeCollection nodes1;
	nodes1.create(Point3d<float>(Vector3d<float>(1, 2, 3)));

	NodeCollection nodes2;
	nodes1.create(Point3d<float>(Vector3d<float>(21, 22, 23)));

	nodes1.merge(nodes2);
	EXPECT_EQ(2, nodes1.get().size());
	EXPECT_EQ(0, nodes1.get().front()->getId());
	EXPECT_EQ(1, nodes1.get().back()->getId());
	EXPECT_TRUE( nodes2.get().empty());

}