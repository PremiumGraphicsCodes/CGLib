#include "stdafx.h"
#include "../Core/PolygonMesh.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(PolygonMeshTest, TestCreateVertex)
{
	PolygonMesh object;
	auto v1 = object.createVertex(Vector3d<float>(1.0f, 0.0f, 0.0f));
	EXPECT_EQ(v1->getId(), 0);
	auto v2 = object.createVertex(Vector3d<float>(1.0f, 1.0f, 0.0f));
	EXPECT_EQ(v2->getId(), 1);

	EXPECT_EQ( v2, object.findVertexById(1) );
}

TEST(PolygonMeshTest, TestMerge)
{
	PolygonMesh object1;
	auto v1 = object1.createVertex(Vector3d<float>(1.0f, 0.0f, 0.0f));
	PolygonMesh object2;
	auto v2 = object2.createVertex(Vector3d<float>(1.0f, 0.0f, 0.0f));
	object1.merge(&object2);
	EXPECT_EQ( 2, object1.getVertices().size() );
	EXPECT_EQ( 0, object2.getVertices().size());
}

TEST(PolygonMeshTest, TestClone)
{
	PolygonMesh object1;
	auto v1 = object1.createVertex(Vector3d<float>(1.0f, 0.0f, 0.0f));
	auto v2 = object1.createVertex(Vector3d<float>(1.0f, 1.0f, 0.0f));
	auto v3 = object1.createVertex(Vector3d<float>(1.0f, 1.0f, 1.0f));
	object1.createFace(v1, v2, v3);
	auto actual = object1.clone();
	delete actual;
}

TEST(PolygonMeshTest, TestAddBox)
{
	PolygonMesh object;
	Box3d<float> box(Vector3d<float>(0.0f, 0.0f, 0.0f), Vector3d<float>(1.0f, 1.0f, 1.0f));
	object.add(box);
	const auto faces = object.getFaces();
	EXPECT_EQ(12, faces.size());
	EXPECT_EQ(Vector3d<float>( 0.0f,  0.0f, -1.0f), faces[0]->getNormal());
	EXPECT_EQ(Vector3d<float>( 0.0f,  0.0f, -1.0f), faces[1]->getNormal());
	EXPECT_EQ(Vector3d<float>( 0.0f,  0.0f,  1.0f), faces[2]->getNormal());
	EXPECT_EQ(Vector3d<float>( 0.0f,  0.0f,  1.0f), faces[3]->getNormal());
	EXPECT_EQ(Vector3d<float>( 1.0f,  0.0f, 0.0f), faces[4]->getNormal());
	EXPECT_EQ(Vector3d<float>( 1.0f,  0.0f, 0.0f), faces[5]->getNormal());
	EXPECT_EQ(Vector3d<float>(-1.0f,  0.0f, 0.0f), faces[6]->getNormal());
	EXPECT_EQ(Vector3d<float>(-1.0f,  0.0f, 0.0f), faces[7]->getNormal());
	EXPECT_EQ(Vector3d<float>( 0.0f,  1.0f, 0.0f), faces[8]->getNormal());
	EXPECT_EQ(Vector3d<float>( 0.0f,  1.0f, 0.0f), faces[9]->getNormal());
	EXPECT_EQ(Vector3d<float>( 0.0f, -1.0f, 0.0f), faces[10]->getNormal());
	EXPECT_EQ(Vector3d<float>( 0.0f, -1.0f, 0.0f), faces[11]->getNormal());

}