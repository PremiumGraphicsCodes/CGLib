#include "gtest/gtest.h"
#include "../IO/PMDFile.h"
#include <fstream>

using namespace Crystal::Math;
using namespace Crystal::IO;

TEST(PMDFileTest, TestWriteHeader)
{
	PMDHeader header("modelname", "comment");
	//std::ostringstream stream(std::ios::binary);
	std::ofstream stream("../TestFile/IO/PMDHeaderTest.pmd", std::ios::binary);
	EXPECT_TRUE( header.write(stream) );
	//auto actual = stream.str();

}

/*
TEST(PMDFileTest, TestToPolygonObject)
{
	PMDHeader header;
	PMDVertices vertices;
	PMDFaces faces;
	PMDFile file(header, vertices, faces);
	auto polygon = file.toPolygonObject();
	delete polygon;
}
*/