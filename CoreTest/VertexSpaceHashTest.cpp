#include "stdafx.h"
#include "../Core/VertexSpaceHash.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(VertexSpaceHashTest, TestGetNeighbor)
{
	VertexSpaceHash hash(1.0f, 100);
	Vertex v1(Vector3d<float>(0.0f, 0.0f, 0.0f));
	Vertex v2(Vector3d<float>(0.5f, 0.0f, 0.0f));
	Vertex v3(Vector3d<float>(-0.5f, 0.0f, 0.0f));
	hash.add(&v1);
	hash.add(&v2);
	hash.add(&v3);
	EXPECT_EQ(3, hash.getNeighbor(Vector3d<float>(0.0, 0.0, 0.0), 1.0f).size());
	EXPECT_EQ(1, hash.getNeighbor(Vector3d<float>(1.0, 0.0, 0.0), 1.0f).size());
	EXPECT_EQ(1, hash.getNeighbor(Vector3d<float>(-1.0, 0.0, 0.0), 1.0f).size());
}
