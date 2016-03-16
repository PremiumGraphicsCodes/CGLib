#include "gtest/gtest.h"
#include "../Polygon/Vertex.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;


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