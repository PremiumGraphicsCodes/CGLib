#include "stdafx.h"

#include "../Core/HalfEdge.h"
#include "../Core/EdgeCollection.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(EdgeCollectionTest, TestCreate)
{
	Vertex v1(Vector3d<float>(0, 0, 0));
	Vertex v2(Vector3d<float>(1, 0, 0));

	HalfEdge e1(&v1, &v2);
	HalfEdge e2(&v2, &v1);
	EdgeCollection edges;
	edges.create(&e1, &e2);
	EXPECT_EQ(1, edges.get().size());
	edges.clear();
}