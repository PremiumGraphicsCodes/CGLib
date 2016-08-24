#include "stdafx.h"

#include "../Core/PolygonRepository.h"
#include "../Core/PolygonBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(PolygonRepositoryTest, TestCreate)
{
	Triangle3d<float> triangle(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder(triangle.toCurve3d());
	PolygonRepository factory;
	auto actual = factory.create(builder);
	EXPECT_EQ(1, actual->getFaces().size());
	EXPECT_EQ(3, actual->getVertices().size());

}

TEST(PolygonRepositoryTest, TestMerge)
{
	 Triangle3d<float> t1(Vector3d<float>(-1,0,0), Vector3d<float>(1,0,0), Vector3d<float>(0,1,0));
	 PolygonBuilder builder(t1.toCurve3d());
	 builder.build();
	 PolygonRepository f1;
	 f1.create(builder);
	 PolygonRepository f2;
	 f2.create(builder);
	 f1.merge(f2);
	 EXPECT_EQ(2, f1.getFaces().size());
	 EXPECT_EQ(0, f2.getFaces().size());
	 EXPECT_EQ(6, f1.getVertices().size());
	 EXPECT_EQ(0, f2.getVertices().size());
}

TEST(PolygonRepositoryTest, TestRemoveFace)
{
	Triangle3d<float> t1(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder(t1.toCurve3d());
	PolygonRepository factory;
	auto f = factory.create(builder);
	factory.remove(f);
	EXPECT_EQ(0, factory.getPolygons().size());
}

TEST(PolygonRepositoryTest, TestDestoryVertexTriangle)
{
	Triangle3d<float> t1(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder(t1.toCurve3d());
	PolygonRepository factory;
	auto polygon = factory.create(builder);
	auto v = factory.getVertices().findById(2);
	factory.destory(v);
	factory.cleaning();
	EXPECT_EQ(0, polygon->getFaces().size());
	//EXPECT_EQ(0, factory.getEdges().size());
	//EXPECT_EQ(0, factory.getVertices().size());
	//EXPECT_EQ(0, factory.getPolygons().size());
}

TEST(PolygonRepositoryTest, TestDestoryVertexQuad)
{
	Quad3d<float> q(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder(q.toCurve3d(1,1));
	PolygonRepository factory;
	auto polygon = factory.create(builder);
	auto v = factory.getVertices().findById(2);
	factory.destory(v);
	factory.cleaning();
	EXPECT_EQ(1, polygon->getFaces().size());
}

TEST(PolygonRepositoryTest, TestDestoryFace)
{
	Triangle3d<float> t1(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder(t1.toCurve3d());
	PolygonRepository factory;
	auto polygon = factory.create(builder);
	factory.destory(polygon->getFaces().front());
	factory.cleaning();
	EXPECT_EQ(0, polygon->getFaces().size());
	EXPECT_EQ(1, factory.getPolygons().size());
}

TEST(PolygonRepositoryTest, TestDestoryEdge)
{
	Triangle3d<float> t1(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder(t1.toCurve3d());
	PolygonRepository factory;
	auto polygon = factory.create(builder);
	auto e = factory.getEdges().findById(0);
	factory.destory(e);
	factory.cleaning();
	EXPECT_EQ(0, polygon->getFaces().size());
}

TEST(PolygonRepositoryTest, TestSimplify)
{
	Triangle3d<float> t1(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder(t1.toCurve3d());
	PolygonRepository factory;
	auto p = factory.create(builder);
	factory.simplify(p, 1);
}

TEST(PolygonRepositoryTest, TestFindDouble)
{
	Triangle3d<float> t1(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	Triangle3d<float> t2(Vector3d<float>(-1, 0, 0), Vector3d<float>(0, -1, 0), Vector3d<float>(1, 0, 0));

	PolygonBuilder builder1(t1.toCurve3d());
	PolygonBuilder builder2(t2.toCurve3d());
	PolygonRepository factory;

	auto p1 = factory.create(builder1);
	auto p2 = factory.create(builder2);

	auto actual = factory.findDouble(p1, p2, 1.0e-6f);
	EXPECT_EQ(2, actual.size());
}

TEST(PolygonRepositoryTest, TestReConnect)
{
	Triangle3d<float> t1(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	Triangle3d<float> t2(Vector3d<float>(-1, 0, 0), Vector3d<float>(0, -1, 0), Vector3d<float>(1, 0, 0));

	PolygonBuilder builder1(t1.toCurve3d());
	PolygonBuilder builder2(t2.toCurve3d());
	PolygonRepository factory;

	auto p1 = factory.create(builder1);
	auto p2 = factory.create(builder2);

	auto actual = factory.findDouble(p1, p2, 1.0e-6f);
	//factory.reconnect(face);
}

TEST(PolygonRepositoryTest, TestFindIsolatedVertices)
{
	VertexRepository vs;
	vs.create(Vector3d<float>(0, 0, 0));
	PolygonRepository factory(vs);
	Triangle3d<float> t1(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder1(t1.toCurve3d());
	factory.create(builder1);

	auto actual = factory.findIsolatedVertices();
	EXPECT_EQ(1, actual.size());
}

TEST(PolygonRepositoryTest, TestSplit)
{
	PolygonRepository factory;
	Triangle3d<float> t1(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder1(t1.toCurve3d());
	auto polygon = factory.create(builder1);
	auto f = polygon->getFaces().front();
	auto e = f->getEdges()[1];
	factory.split(polygon, e);
	EXPECT_EQ(2, factory.getFaces().size());
	EXPECT_EQ(6, factory.getEdges().size());
	EXPECT_EQ(4, factory.getVertices().size());
	auto f1 = factory.getFaces().get().front();
	EXPECT_EQ(Vector3d<float>(-1, 0, 0), f1->getEdges().front()->getStart()->getPosition());
	EXPECT_EQ(Vector3d<float>(1, 0, 0), f1->getEdges().front()->getNext()->getStart()->getPosition());
	EXPECT_EQ(Vector3d<float>(0.5, 0.5, 0), f1->getEdges().front()->getNext()->getNext()->getStart()->getPosition());
	
	auto f2 = factory.getFaces().get().back();
	EXPECT_EQ(Vector3d<float>(-1, 0, 0), f2->getEdges().front()->getStart()->getPosition());
	EXPECT_EQ(Vector3d<float>(0.5, 0.5, 0), f2->getEdges().front()->getNext()->getStart()->getPosition());
	EXPECT_EQ(Vector3d<float>(0, 1, 0), f2->getEdges().front()->getNext()->getNext()->getStart()->getPosition());
}