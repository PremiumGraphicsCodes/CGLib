#include "stdafx.h"
#include "../Core/PolygonMesh.h"
#include "../Core/PolygonFactory.h"
#include "../Core/PolygonBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(PolygonMeshTest, TestFromQuad)
{
	const Quad<float> quad(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder(quad.toCurve3d());
	PolygonFactory factory;
	auto polygon = factory.create(builder);
	EXPECT_EQ(4, polygon->getVertices().size());
	EXPECT_EQ(2, polygon->getFaces().size());
}

TEST(PolygonMeshTest, TestFromCircle)
{
	const Circle3d<float> circle(1.0, Vector3d<float>(0, 0, 0), Quaternion<float>());
	PolygonBuilder builder(circle.toCurve(3));
	PolygonFactory factory;
	auto polygon = factory.create(builder);
	EXPECT_EQ(4, polygon->getVertices().size());
	EXPECT_EQ(3, polygon->getFaces().size());
}

TEST(PolygonMeshTest, TestFromTriangle)
{
	const Triangle3d<float> triangle;
	PolygonBuilder builder(triangle.toCurve3d());
	PolygonFactory factory;
	auto polygon = factory.create(builder);
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
*/
TEST(PolygonMeshTest, TestSplitByCenter)
{
	Triangle3d<float> triangle(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder(triangle.toCurve3d());
	PolygonFactory factory;
	auto polygon = factory.create(builder);
	auto f = polygon->getFaces().front();
	factory.splitByCenter(polygon, f);
	EXPECT_EQ(3, polygon->getFaces().size());
	EXPECT_EQ(4, polygon->getVertices().size());
	EXPECT_EQ(9, polygon->getEdges().size());
}

/*
#include "../Core/Edge.h"

TEST(PolygonMeshTest, TestGetShortestEdge)
{
	Quad<float> q(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder(q.toCurve3d());
	PolygonFactory factory;
	auto polygon = factory.create(builder);
	factory.splitByCenter(polygon, polygon->getFaces().front());
	auto actual = polygon->getShortestEdge();
	EXPECT_FLOAT_EQ(0.4714045, actual->getLength());
}

/*
TEST(PolygonMeshTest, TestSimplify)
{
	Quad<float> q(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonFactory factory;
	auto polygon = factory.create(q.toCurve3d());
	factory.splitByCenter(polygon, polygon->getFaces().front());
	auto edge = polygon->getShortestEdge();
	polygon->simplify(edge);
	auto faces = polygon->getFaces();
	for (auto f : faces) {
		if (f->getArea() < Tolerance<float>::getLooseTolerance()) {
			factory.remove(f);
		}
	}
	polygon->cleaning();
	EXPECT_EQ(1, polygon->getFaces().size());
	EXPECT_EQ(3, polygon->getVertices().size());

}

/*
class PolygonReductionAlgo
{
public:
	void collapse(Vertex* u, Vertex* v) {
		if (!u) {
			delete u;
			return;
		}
		auto neighbors = u->getNeighbors();
		auto faces = u->getFaces();
		for (auto f : faces) {
			if (f->has(v)) {
				factory.remove(f);
			}
		}
		auto faces = u->getFaces();
		for (auto f : faces) {
			f->replace(u, v);
		}
		delete u;

	}

	void reduce(PolygonMesh* polygon) {
	}
private:
	PolygonFactory& factory;
};

TEST(PolygonReductionTest, Test)
{
	PolygonReductionAlgo algo;
}
*/