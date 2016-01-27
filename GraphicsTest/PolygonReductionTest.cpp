#include "gtest/gtest.h"
#include "../Graphics/PolygonReduction.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics::Experiment;


TEST(PolygonReductionTest, TestRemoveOverlappedVertices)
{
	TriangleMesh mesh;
	const auto v1 = mesh.createVertex( Vector3d<float>(0, 0, 0) );
	const auto v2 = mesh.createVertex( Vector3d<float>(1, 0, 0) );
	const auto v3 = mesh.createVertex( Vector3d<float>(0, 1, 0) );
	const auto v4 = mesh.createVertex( Vector3d<float>(-1, 0, 0) );
	const auto v5 = mesh.createVertex( Vector3d<float>(0, 0, 0) );
	const auto v6 = mesh.createVertex( Vector3d<float>(0, 1, 0) );

	mesh.removeOverlappedVerticies();

	EXPECT_EQ(4, mesh.getVertices().size());
}

TEST(PolygonReductionTest, TestCreateFacesVertices)
{
	TriangleMesh mesh;
	const auto v1 = mesh.createVertex(Vector3d<float>(0, 0, 0));
	const auto v2 = mesh.createVertex(Vector3d<float>(1, 0, 0));
	const auto v3 = mesh.createVertex(Vector3d<float>(0, 1, 0));
	const auto v4 = mesh.createVertex(Vector3d<float>(-1, 0, 0));
	const auto v5 = mesh.createVertex(Vector3d<float>(0, 0, 0));
	const auto v6 = mesh.createVertex(Vector3d<float>(0, 1, 0));

	auto f1 = mesh.createFace({ v1, v2, v3 });
	auto f2 = mesh.createFace({ v4, v5, v6 });

	EXPECT_TRUE(f1->hasVertex(v1));
	EXPECT_FALSE(f1->hasVertex(v5));
	EXPECT_FALSE(f1->isNeighbor(*f2));

	f1->replaceVertex(v1, v5);
	EXPECT_TRUE(f1->isNeighbor(*f2));

	EXPECT_FALSE(f1->hasVertex(v1));
	EXPECT_TRUE(f1->hasVertex(v5));
}


TEST(PolygonReductionTest, TestTriangleFace)
{
	Vertex v1(Vector3d<float>(0,0,0));
	Vertex v2(Vector3d<float>(1, 0, 0));
	Vertex v3(Vector3d<float>(0, 1, 0));

	TriangleFace f({ &v1,&v2,&v3 });
	EXPECT_EQ(&f, v1.getFaces().front());
	EXPECT_EQ(&f, v2.getFaces().front());
	EXPECT_EQ(&f, v3.getFaces().front());

}

TEST(PolygonReductionTest, TestComputeCost)
{
	Vertex v1(Vector3d<float>(0, 0, 0));
	Vertex v2(Vector3d<float>(1, 0, 0));
	Vertex v3(Vector3d<float>(0, 1, 0));

	TriangleFace f({ &v1,&v2,&v3 });
	auto actual = v1.computeCost();
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