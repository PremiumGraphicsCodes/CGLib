#include "stdafx.h"
#include "../Core/Vertex.h"
#include "../Core/VertexCollection.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(VertexCollectionTest, TestSort)
{
	VertexCollection vertices1;
	vertices1.create(Vector3d<float>(0.0f, 0.0f, 0.0f));
	vertices1.create(Vector3d<float>(0.0f, 0.0f, 0.0f));
	vertices1.create(Vector3d<float>(1.0f, 0.0f, 0.0f));
	vertices1.sort();
	EXPECT_EQ(2, vertices1.size());
}


TEST(VertexCollectionTest, TestMerge)
{
	VertexCollection vertices1;
	vertices1.create(Vector3d<float>(0.0f, 0.0f, 0.0f));
	VertexCollection vertices2;
	vertices2.create(Vector3d<float>(0.0f, 0.0f, 0.0f));
	vertices1.merge(vertices2);
	EXPECT_EQ( 2, vertices1.size() );
	EXPECT_EQ( 0, vertices2.size() );
}

#include "../Core/Face.h"

TEST(VertexTest, TestComputeCollapseCost)
{
	Vertex v1(Vector3d<float>(-1, 0, 0), 0);
	Vertex v2(Vector3d<float>( 1, 0, 0), 0);
	Vertex v3(Vector3d<float>( 1, 1, 0), 0);
	Face f(&v1, &v2, &v3);
	v1.calculateCollapseCost();
}


//
//TEST(PolygonReductionTest, TestReduceTo)
//{
//	TriangleMesh mesh;
//	const auto v1 = mesh.createVertex(Vector3d<float>(0, 0, 0));
//	const auto v2 = mesh.createVertex(Vector3d<float>(1, 0, 0));
//	const auto v3 = mesh.createVertex(Vector3d<float>(0, 1, 0));
//	const auto v4 = mesh.createVertex(Vector3d<float>(-1, 0, 0));
//
//	auto f1 = mesh.createFace({ v1, v2, v3 });
//	auto f2 = mesh.createFace({ v1, v4, v3 });
//	mesh.reduceTo(3);
//}