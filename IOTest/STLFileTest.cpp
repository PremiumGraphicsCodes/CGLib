#include "gtest/gtest.h"
 
#include "../IO/STLFile.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

using T = float;

TEST( STLFileTest, TestReadAscii )
{
	std::stringstream stream;
	stream
		<< "solid cube-ascii" << std::endl
		<< "facet normal  0.0  0.0 1.0" << std::endl
		<< "	outer loop" << std::endl
		<< "		vertex  0.0  0.0  1.0" << std::endl
		<< "		vertex  1.0  0.0  1.0" << std::endl
		<< "		vertex  0.0  1.0  1.0" << std::endl
		<< "endloop" << std::endl
		<< "endfacet" << std::endl
		<< "facet normal 0.0 0.0 1.0" << std::endl
		<< "	outer loop" << std::endl
		<< "		vertex  1.0  1.0  1.0" << std::endl
		<< "		vertex  0.0  1.0  1.0" << std::endl
		<< "		vertex  1.0  0.0  1.0" << std::endl
		<< "	endloop" << std::endl
		<< "endfacet" << std::endl
		<< "endsolid" << std::endl;

	STLFileReader reader;
	reader.readASCII(stream);
	STLFile file = reader.getFile();

	const Vector3d<T> normal1(0.0, 0.0, 1.0);
	const std::vector< Vector3d<T> > positions1 = {
		Vector3d<T>(0.0, 0.0, 1.0),
		Vector3d<T>(1.0, 0.0, 1.0),
		Vector3d<T>(0.0, 1.0, 1.0)
	};
	const Vector3d<T> normal2(0.0, 0.0, 1.0);
	const std::vector< Vector3d<T> > positions2 = {
		Vector3d<T>(1.0, 1.0, 1.0),
		Vector3d<T>(0.0, 1.0, 1.0),
		Vector3d<T>(1.0, 0.0, 1.0)
	};
	const STLCellVector cells{
		STLCell(positions1, normal1),
		STLCell(positions2, normal2)
	};

	STLFile expected;
	expected.setCells(cells);
	expected.setTitle(" cube-ascii");

	EXPECT_EQ( expected, file );
}

TEST(STLFileTest, TestWriteASCII)
{
	std::ostringstream stream;
	STLFile file;

	const Vector3d<T> normal1(0.0, 0.0, 1.0);
	const std::vector< Vector3d<T> > positions1 = {
		Vector3d<T>(0.0, 0.0, 1.0),
		Vector3d<T>(1.0, 0.0, 1.0),
		Vector3d<T>(0.0, 1.0, 1.0)
	};
	const Vector3d<T> normal2(0.0, 0.0, 1.0);
	const std::vector< Vector3d<T> > positions2 = {
		Vector3d<T>(1.0, 1.0, 1.0),
		Vector3d<T>(0.0, 1.0, 1.0),
		Vector3d<T>(1.0, 0.0, 1.0)
	};
	const STLCellVector cells{
		STLCell(positions1, normal1),
		STLCell(positions2, normal2)
	};

	file.setTitle("cube-ascii");
	file.setCells(cells);
	STLFileWriter writer(file);
	writer.writeASCII(stream);

	std::stringstream expected;
	expected
		<< "solid cube-ascii" << std::endl
		<< "facet normal 0 0 1" << std::endl
		<< "outer loop" << std::endl
		<< "vertex 0 0 1" << std::endl
		<< "vertex 1 0 1" << std::endl
		<< "vertex 0 1 1" << std::endl
		<< "endloop" << std::endl
		<< "endfacet" << std::endl
		<< "facet normal 0 0 1" << std::endl
		<< "outer loop" << std::endl
		<< "vertex 1 1 1" << std::endl
		<< "vertex 0 1 1" << std::endl
		<< "vertex 1 0 1" << std::endl
		<< "endloop" << std::endl
		<< "endfacet" << std::endl
		<< "endsolid" << std::endl;

	const std::string& actual = stream.str();
	EXPECT_EQ(expected.str(), stream.str());
}

TEST(STLFileTest, TestWriteBinary)
{
	std::ostringstream stream;
	STLFile file;
	file.setTitle("Test");
	STLFileWriter writer(file);
	writer.writeBinary(stream);
	const std::string& actual = stream.str();
	//EXPECT_EQ(80, actual.size());
}

#include "../IO/POVFile.h"

TEST(STLFileTest, TestReadBinary)
{
	STLFileReader reader;
	reader.read("../TestFile/IO/cube-binary.stl");
}


/*
TEST(STLFileTest, TestToSurface)
{
	STLCellVector cells;
	STLCell cell;
	Vector3d<float> v0(0.0, 0.0, 0.0);
	Vector3d<float> v1(1.0, 0.0, 0.0);
	Vector3d<float> v2(1.0, 1.0, 0.0);
	cell.setPositions({ v0,v1,v2 });
	cells.push_back(cell);
	STLFile file(cells, "");
	const auto actual = file.toSurface();
	EXPECT_EQ(1, actual.getFaces().size());
	EXPECT_EQ(3, actual.getVertices().size());
	//EXPECT_EQ(v2, actual.getVertices()[2]);
}
*/