#include "stdafx.h"
#include "../Core/Vertex.h"
#include "../Core/HalfEdge.h"

#include "../Core/VertexRepository.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(VertexCollectionTest, TestSort)
{
	VertexRepository vertices;
	auto v1 = vertices.create(Vector3d<float>(0.0f, 0.0f, 0.0f));
	auto v2 = vertices.create(Vector3d<float>(0.0f, 0.0f, 0.0f));
	auto v3 = vertices.create(Vector3d<float>(1.0f, 0.0f, 0.0f));
	HalfEdge e1(v1, v2);
	HalfEdge e2(v2, v3);
	HalfEdge e3(v3, v1);
	vertices.sort();
	EXPECT_EQ(2, vertices.size());
	vertices.clear();
}


TEST(VertexCollectionTest, TestMerge)
{
	VertexRepository vertices1;
	vertices1.create(Vector3d<float>(0.0f, 0.0f, 0.0f));
	VertexRepository vertices2;
	vertices2.create(Vector3d<float>(0.0f, 0.0f, 0.0f));
	vertices1.merge(vertices2);
	EXPECT_EQ( 2, vertices1.size() );
	EXPECT_EQ( 0, vertices2.size() );
	vertices1.clear();
	vertices2.clear();
}

#include "../Core/Face.h"
/*
TEST(VertexTest, TestComputeCollapseCost)
{
	Vertex v1(Vector3d<float>(-1, 0, 0), 0);
	Vertex v2(Vector3d<float>( 1, 0, 0), 0);
	Vertex v3(Vector3d<float>( 1, 1, 0), 0);
	Vertex v4(Vector3d<float>(-1, 1, 1), 0);

	Face f1(&v1, &v2, &v3);
	Face f2(&v1, &v3, &v4);

	v3.calculateCollapseCost();
}
*/