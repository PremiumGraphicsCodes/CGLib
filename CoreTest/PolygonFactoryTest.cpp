#include "stdafx.h"

#include "../Core/PolygonFactory.h"
#include "../Core/PolygonBuilder.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(PolygonFactoryTest, TestCreate)
{
	Triangle3d<float> triangle(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonBuilder builder(triangle.toCurve3d());
	PolygonFactory factory;
	auto actual = factory.create(builder);
	EXPECT_EQ(1, actual->getFaces().size());
	EXPECT_EQ(3, actual->getVertices().size());

}

/*
TEST(PolygonFactoryTest, TestMerge)
{
	 Triangle3d<float> t1(Vector3d<float>(-1,0,0), Vector3d<float>(1,0,0), Vector3d<float>(0,1,0));
	 PolygonFactory f1;
	 f1.create(t1.toCurve3d());
	 PolygonFactory f2;
	 f2.create(t1.toCurve3d());
	 f1.merge(f2);
	 EXPECT_EQ(2, f1.getFaces().size());
	 EXPECT_EQ(0, f2.getFaces().size());
	 EXPECT_EQ(6, f1.getVertices().size());
	 EXPECT_EQ(0, f2.getVertices().size());
}

TEST(PolygonFactoryTest, TestRemove)
{
	Triangle3d<float> t1(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonFactory factory;
	auto f = factory.create(t1.toCurve3d());
	factory.remove(f);
	EXPECT_EQ(0, factory.getFaces().size());
	EXPECT_EQ(0, factory.getVertices().size());
	EXPECT_EQ(0, factory.getPolygons().size());
}

TEST(PolygonFactoryTest, TestSimplify)
{
	Triangle3d<float> t1(Vector3d<float>(-1, 0, 0), Vector3d<float>(1, 0, 0), Vector3d<float>(0, 1, 0));
	PolygonFactory factory;
	auto p = factory.create(t1.toCurve3d());
	factory.simplify(p, 1);
}
*/