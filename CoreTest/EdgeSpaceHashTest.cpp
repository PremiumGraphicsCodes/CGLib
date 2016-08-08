#include "stdafx.h"
#include "../Core/Vertex.h"
#include "../Core/EdgeSpaceHash.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(EdgeSpaceHashTest, TestGetNeighbor)
{
	EdgeSpaceHash hash(1.0f, 100);
	Vertex v1(Vector3d<float>(0.0f, 0.0f, 0.0f));
	Vertex v2(Vector3d<float>(5.0f, 0.0f, 0.0f));
	Vertex v3(Vector3d<float>(5.0f, 5.0f, 0.0f));
	HalfEdge e1(&v1, &v2);
	HalfEdge e2(&v2, &v3);
	hash.add(&e1);
	hash.add(&e2);
	EXPECT_EQ(1, hash.getNeighbor(Vector3d<float>(0.0, 0.0, 0.0)).size());
	EXPECT_EQ(1, hash.getNeighbor(Vector3d<float>(2.0, 0.0, 0.0)).size());
	EXPECT_EQ(0, hash.getNeighbor(Vector3d<float>(10.0, 0.0, 0.0)).size());
}
