#include "gtest/gtest.h"

#include "../Math/Triangle.h"
#include "../IO/POVFile.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::IO;

TEST(POVFileTest, TestWriteScene)
{
	POVFile file;
	std::string dest("../TestFile/IO/POVFileTestWrite.pov");

	TriangleMesh mesh;
	auto v1 = mesh.createVertex(Vector3d<float>(0, 0, 0));
	auto v2 = mesh.createVertex(Vector3d<float>(1, 0, 0));
	auto v3 = mesh.createVertex(Vector3d<float>(1, 1, 0));
	mesh.createFace(v1, v2, v3);
	EXPECT_TRUE(file.writeScene(dest, mesh));
}

TEST(POVFileTest, TestWriteInc)
{
	POVFile file;
	std::string dest("../TestFile/IO/POVFileTestWrite.inc");

	TriangleMesh mesh;
	auto v1 = mesh.createVertex(Vector3d<float>(0, 0, 0));
	auto v2 = mesh.createVertex(Vector3d<float>(1, 0, 0));
	auto v3 = mesh.createVertex(Vector3d<float>(1, 1, 0));
	mesh.createFace(v1, v2, v3);
	EXPECT_TRUE(file.writeScene(dest, mesh));
}