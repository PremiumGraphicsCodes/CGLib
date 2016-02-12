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