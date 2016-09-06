#include "stdafx.h"

#include "../Core/Node.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(NodeTest, Test)
{
	Vertex v1(Vector3d<float>(0, 0, 0), Vector3d<float>(0,0,1));
	Vertex v2(Vector3d<float>(0.1, 0, 0), Vector3d<float>(0, 0, 1));
	Node node;
	node.add(&v1);
	node.add(&v2);
	const auto& point = node.merge();
	EXPECT_EQ(Vector3d<float>(0.05, 0, 0), point.getPosition());
	EXPECT_EQ(Vector3d<float>(0, 0, 1), point.getNormal());
}