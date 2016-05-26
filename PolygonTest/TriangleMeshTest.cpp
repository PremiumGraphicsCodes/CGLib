#include "gtest\gtest.h"

#include "../Polygon/PolygonMesh.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

TEST(TriangleMeshTest, Test)
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