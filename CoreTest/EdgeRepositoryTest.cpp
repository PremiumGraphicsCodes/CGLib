#include "stdafx.h"

#include "../Core/HalfEdge.h"
#include "../Core/EdgeCollection.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(EdgeRepositoryTest, TestCreate)
{
	Vertex v1(Vector3d<float>(0, 0, 0));
	Vertex v2(Vector3d<float>(1, 0, 0));

	HalfEdge e1(&v1, &v2);
	HalfEdge e2(&v2, &v1);
	EdgeCollection edges;
	auto actual = edges.create(&e1, &e2);
	EXPECT_EQ(1, edges.get().size());
	EXPECT_EQ(0, actual->getId());
	edges.clear();
}