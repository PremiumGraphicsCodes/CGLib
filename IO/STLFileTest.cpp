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

	STLFile file;
	file.readASCII(stream);

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
	file.writeASCII(stream);

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
	file.writeBinary(stream);
	const std::string& actual = stream.str();
	//EXPECT_EQ(80, actual.size());
}