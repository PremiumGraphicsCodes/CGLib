#include "gtest/gtest.h"
#include "../Polygon/PolygonObject.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

TEST(PolygonObjectTest, TestCreateVertex)
{
	PolygonObject object;
	auto v1 = object.createVertex(Vector3d<float>(1.0f, 0.0f, 0.0f));
	EXPECT_EQ(v1->getId(), 0);
	auto v2 = object.createVertex(Vector3d<float>(1.0f, 1.0f, 0.0f));
	EXPECT_EQ(v2->getId(), 1);

	EXPECT_EQ( v2, object.findVertexById(1) );
}

TEST(PolygonObjectTest, TestMerge)
{
	PolygonObject object1;
	auto v1 = object1.createVertex(Vector3d<float>(1.0f, 0.0f, 0.0f));
	PolygonObject object2;
	auto v2 = object2.createVertex(Vector3d<float>(1.0f, 0.0f, 0.0f));
	object1.merge(&object2);
	EXPECT_EQ( 2, object1.getVertices().size() );
	EXPECT_EQ( 0, object2.getVertices().size());

}