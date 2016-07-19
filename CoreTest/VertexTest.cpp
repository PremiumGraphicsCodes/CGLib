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