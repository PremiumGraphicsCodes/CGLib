#include "stdafx.h"
#include "../Core/PolygonMesh.h"
#include "../Core/PolygonFactory.h"
#include "../Core/PolygonBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(PolygonMeshTest, TestFromQuad)
{
	const Quad3d<float> quad(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder(quad.toCurve3d(1, 1));
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

TEST(PolygonMeshTest, TestMerge)
{
	const Quad3d<float> quad(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder(quad.toCurve3d(1,1));
	PolygonFactory factory;
	auto p1 = factory.create(builder);
	auto p2 = factory.create(builder);
	p1->merge(*p2);
	EXPECT_EQ( 4, p1->getFaces().size() );
	EXPECT_EQ( 0, p2->getFaces().size() );
}

TEST(PolygonMeshTest, TestSplitByNode)
{
	const Quad3d<float> quad(Vector3d<float>(0, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder( quad.toCurve3d(1, 1) );
	PolygonFactory factory;
	auto polygon = factory.create(builder);
	auto f = polygon->getFaces().front();
	factory.splitByNode(polygon, f);
	EXPECT_EQ(5, polygon->getFaces().size());
	EXPECT_EQ(7, polygon->getVertices().size());
}

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

TEST(PolygonMeshTest, TestMergeDouble)
{
	Triangle3d<float> t1(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	Triangle3d<float> t2(Vector3d<float>(-1, 0, 0), Vector3d<float>(0, -1, 0), Vector3d<float>(1, 0, 0));

	PolygonBuilder builder1(t1.toCurve3d());
	PolygonBuilder builder2(t2.toCurve3d());
	PolygonFactory factory;

	auto p1 = factory.create(builder1);
	auto p2 = factory.create(builder2);

	p1->mergeDouble(p2, 1.0e-6f);
	auto vertices1 = p1->getVertices();
	auto vertices2 = p2->getFaces().front()->getVertices();
	EXPECT_EQ(0, vertices2.front()->getId());
	EXPECT_EQ(1, vertices2.back()->getId());
}

/*
#include "../Core/HalfEdge.h"

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