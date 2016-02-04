#include "gtest\gtest.h"

#include "../Polygon/PolygonObject.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

TEST(TriangleMeshTest, Test)
{
	PolygonObject mesh;
	auto p1 = mesh.createPosition(Vector3d<float>(0.0, 0.0, 0.0));
	auto p2 = mesh.createPosition(Vector3d<float>(1.0, 0.0, 0.0));
	auto p3 = mesh.createPosition(Vector3d<float>(1.0, 1.0, 0.0));
	auto p4 = mesh.createPosition(Vector3d<float>(0.0, 1.0, 0.0));
	mesh.createVertex(p1);
	mesh.createVertex(p2);
	mesh.createVertex(p3);
	mesh.createVertex(p4);
	std::vector<int> ids{ 0, 1, 2, 3 };
	auto actual = mesh.createFaces(ids);
	EXPECT_EQ(2, actual.size());
}