#include "gtest/gtest.h"
#include "../Polygon/Vertex.h"
#include "../Polygon/PolygonObject.h"
#include "../IO/PMDFile.h"
#include <fstream>

using namespace Crystal::Math;
using namespace Crystal::Polygon;
using namespace Crystal::IO;

TEST(PMDFileTest, TestWriteHeader)
{
	PMDHeader header("modelname", "comment");
	//std::ostringstream stream(std::ios::binary);
	std::ofstream stream("../TestFile/IO/PMDHeaderTest.pmd", std::ios::binary);
	EXPECT_TRUE( header.write(stream) );
	//auto actual = stream.str();

}

TEST(PMDFileTest, TestFromPolygonObject)
{
	PolygonObject object;
	Triangle<float> triangle(Vector3d<float>(0.0, 0.0, 0.0), Vector3d<float>(1.0, 0.0, 0.0), Vector3d<float>(1.0, 1.0, 0.0));
	object.add(triangle);
	PMDFile file(object);
}

/*
TEST(PMDFileTest, TestToPolygonObject)
{
	PMDHeader header;
	//PMDVertices vertices;
	//PMDFaces faces;
	PMDFile file(); header, vertices, faces);
	auto polygon = file.toPolygonObject();
	delete polygon;
}
*/