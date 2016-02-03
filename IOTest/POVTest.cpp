#include "gtest/gtest.h"

#include "../Math/Triangle.h"
#include "../Polygon/TriangleMesh.h"
#include "../IO/POVFile.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::IO;

TEST(POVFileTest, TestWriteScene)
{
	POVFile file;
	std::string dest("../TestFile/IO/POVFileTestWrite.pov");

	TriangleMesh mesh;
	auto p1 = mesh.createPosition(Vector3d<float>(0, 0, 0));
	auto p2 = mesh.createPosition(Vector3d<float>(1, 0, 0));
	auto p3 = mesh.createPosition(Vector3d<float>(1, 1, 0));
	auto v1 = mesh.createVertex(p1);
	auto v2 = mesh.createVertex(p2);
	auto v3 = mesh.createVertex(p3);
	mesh.createFace(v1, v2, v3);
	EXPECT_TRUE(file.writeScene(dest, { &mesh }));
}

TEST(POVFileTest, TestWriteInc)
{
	POVFile file;
	std::string dest("../TestFile/IO/POVFileTestWrite.inc");

	TriangleMesh mesh;
	auto p1 = mesh.createPosition(Vector3d<float>(0, 0, 0));
	auto p2 = mesh.createPosition(Vector3d<float>(1, 0, 0));
	auto p3 = mesh.createPosition(Vector3d<float>(1, 1, 0));
	auto v1 = mesh.createVertex(p1);
	auto v2 = mesh.createVertex(p2);
	auto v3 = mesh.createVertex(p3);
	mesh.createFace(v1, v2, v3);
	EXPECT_TRUE(file.writeInc(dest, { &mesh }));
}