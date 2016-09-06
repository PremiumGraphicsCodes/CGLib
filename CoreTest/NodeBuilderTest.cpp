#include "stdafx.h"

#include "../Core/Node.h"
#include "../Core/NodeBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(NodeBuilderTest, TestBuild)
{
	Vertex v1(Vector3d<float>(0, 0, 0));
	Vertex v2(Vector3d<float>(1, 0, 0));
	std::list<Vertex*> vertices = { &v1, &v2 };
	NodeBuilder builder(vertices);
	const auto& nodes = builder.build(0.1f);
	EXPECT_EQ(2, nodes.size());
	for (auto n : nodes) {
		delete n;
	}
}

TEST(NodeBuilderTest, TestBuild2)
{
	Vertex v1(Vector3d<float>(0, 0, 0));
	Vertex v2(Vector3d<float>(1, 0, 0));
	std::list<Vertex*> vertices = { &v1, &v2 };
	NodeBuilder builder(vertices);
	const auto& nodes = builder.build(1.1f);
	EXPECT_EQ(1, nodes.size());
	for (auto n : nodes) {
		delete n;
	}
}