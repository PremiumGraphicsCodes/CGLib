#include "stdafx.h"
#include "../Core/PolygonMesh.h"
#include "../Core/PolygonFactory.h"


using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(PolygonMeshTest, TestFromQuad)
{
	const Quad<float> quad(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	Curve3d<float> curve = quad.toCurve3d();

	PolygonFactory factory;
	auto polygon = factory.create(curve);
	EXPECT_EQ(4, polygon->getVertices().size());
	EXPECT_EQ(2, polygon->getFaces().size());
}

TEST(PolygonMeshTest, TestFromCircle)
{
	const Circle3d<float> circle(1.0, Vector3d<float>(0, 0, 0), Quaternion<float>());
	CircularCurve3d<float> curve = circle.toCurve(3);

	PolygonFactory factory;
	auto polygon = factory.create(curve);
	EXPECT_EQ(4, polygon->getVertices().size());
	EXPECT_EQ(3, polygon->getFaces().size());
}

TEST(PolygonMeshTest, TestFromTriangle)
{
	const Triangle3d<float> triangle;
	auto curve = triangle.toCurve3d();

	PolygonFactory factory;
	auto polygon = factory.create(curve);
	EXPECT_EQ(3, polygon->getVertices().size());
	EXPECT_EQ(1, polygon->getFaces().size());
}

/*
TEST(PolygonFactoryTest, TestCreateFaces)
{
	PolygonMesh mesh;
	auto p1 = mesh.createVertex(Vector3d<float>(0.0, 0.0, 0.0));
	auto p2 = mesh.createVertex(Vector3d<float>(1.0, 0.0, 0.0));
	auto p3 = mesh.createVertex(Vector3d<float>(1.0, 1.0, 0.0));
	auto p4 = mesh.createVertex(Vector3d<float>(0.0, 1.0, 0.0));
	std::vector<int> ids{ 0, 1, 2, 3 };
	auto actual = mesh.createFaces(ids);
	EXPECT_EQ(2, actual.size());
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

TEST(PolygonMeshTest, TestSplitByNode)
{
	const Quad<float> quad(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	Curve3d<float> curve = quad.toCurve3d();
	PolygonMesh polygon;
	polygon.create(curve);
	auto f = polygon.getFaces().get().front();
	polygon.splitByNode(f);
	EXPECT_EQ(5, polygon.getFaces().size());
	EXPECT_EQ(7, polygon.getVertices().size());
}

TEST(PolygonMeshTest, TestSplitByCenter)
{
	Triangle3d<float> triangle(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonMesh polygon;
	polygon.create(triangle.toCurve3d());
	auto f = polygon.getFaces().get().front();
	polygon.splitByCenter(f);
	EXPECT_EQ(3, polygon.getFaces().size());
	EXPECT_EQ(4, polygon.getVertices().size());
}
*/

#include "../Core/Edge.h"
/*
TEST(PolygonMeshTest, TestSimplify)
{
	Quad<float> q(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonFactory factory;
	factory.add( q.toCurve3d() );
	auto polygon = factory.create(0);
	auto v0 = polygon->getVertices().get().front();
	auto v1 = polygon->getVertices().get().front();
	Edge e(v0, v1, 0);
	polygon->simplify(e);
	auto faces = polygon->getFaces();
	polygon->cleaning();
	EXPECT_EQ(1, polygon->getFaces().size());
	EXPECT_EQ(3, polygon->getVertices().size());

}
*/