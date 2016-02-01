#include "gtest/gtest.h"
 
#include "../Graphics/IBuffer.h"

#include "../IO/OBJFile.h"
#include "../IO/Helper.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Polygon;
using namespace Crystal::IO;

using T = float;


::std::ostream& operator<<(::std::ostream& os, const OBJFace& face) {
	os << "faces " << face.getVertexIndices().size() << std::endl;
	for (unsigned int i : face.getVertexIndices()) {
		os << " " << i;
	}
	os << std::endl;
	os << "normals " << face.getNormalIndices().size() << std::endl;
	for (unsigned int i : face.getNormalIndices()) {
		os << " " << i;
	}
	os << std::endl;
	os << "texIds " << face.getTexIndices().size() << std::endl;
	for (unsigned int i : face.getTexIndices()) {
		os << " " << i;
	}
	os << std::endl;
	return os;
}


/*
::std::ostream& operator<<(::std::ostream& os, const OBJFile& file) {
	for (const OBJFace& f : file.getFaces()) {
		os << f;
	}
	for (const OBJMTLLib& lib : file.getLibs() ) {
		os << lib;
	}

	os << std::endl;
	return os;
}
*/

TEST(OBJFileTest, TestReadVertices)
{
	std::stringstream stream;
	stream
		<< "v 0.1 0.2 0.3" << std::endl
		<< "vt 0.5 1.0" << std::endl
		<< "vn 1.0 0.0 0.0" << std::endl;
	OBJFileReader reader;
	OBJFile file = reader.read(stream);

	const auto actual = file.getGroups().front();

	EXPECT_EQ( Vector3d<T>(0.1f, 0.2f, 0.3f), actual.getPositions().get(0) );
	EXPECT_EQ( Vector3d<T>(0.5f, 1.0f, 0.0f), actual.getTexCoords().get(0) );
	EXPECT_EQ( Vector3d<T>(1.0f, 0.0f, 0.0f), actual.getNormals().get(0) );
}

TEST(OBJFileTest, TestReadFaces)
{
	std::stringstream stream;
	stream
		<< "f 1 2 3" << std::endl
		<< "f 3/1 4/2 5/3" << std::endl
		<< "f 1//1 2//2 3//3 4//4 "<< std::endl
		<< "f 6/4/1 3/5/3 7/6/5" << std::endl;

	OBJFileReader reader;
	OBJFile file =reader.read(stream);

	const std::vector<OBJFace> expected = {
		OBJFace({ 1, 2, 3 } ),
		OBJFace({ 3, 4, 5 }, { 1, 2, 3 } ),
		OBJFace({ 1, 2, 3, 4 }, {}, {1, 2, 3, 4}),
		OBJFace({ 6, 3, 7 }, { 4, 5, 6 }, { 1, 3, 5 })
	};
	EXPECT_EQ( expected, file.getGroups().front().getFaces() );
}

TEST(OBJFileTest, TestReadComments)
{
	std::stringstream stream;
	stream
		<< "# comment1" << std::endl
		<< "v 0.0 0.0 0.0" << std::endl
		<< "# comment2" << std::endl;

	const OBJFileReader file(stream);

	OBJFile expected;
	OBJGroup group;
	//group.setPositions( {Vector3d<T>(0.0, 0.0, 0.0)} );
	//expected.setGroups({ group });
	//EXPECT_EQ( expected, file );
}

TEST(OBJFileTest, TestReadSquare)
{
	std::stringstream stream;
	stream
		<< "v 0.0 2.0 0.0" << std::endl
		<< "v 0.0 0.0 0.0" << std::endl
		<< "v 2.0 0.0 0.0" << std::endl
		<< "v 2.0 2.0 0.0" << std::endl
		<< "f 1 2 3 4" << std::endl;
	const OBJFileReader actual(stream);

	OBJFile expected;
	Buffer3d<T> positions;
	positions.add(Vector3d<T>(0.0, 2.0, 0.0));
	positions.add(Vector3d<T>(0.0, 0.0, 0.0));
	positions.add(Vector3d<T>(2.0, 0.0, 0.0));
	positions.add(Vector3d<T>(2.0, 2.0, 0.0));
	OBJGroup group;
	group.setPositions( positions );
	OBJFace face({ 1, 2, 3, 4 });
	group.setFaces({ face });
	//expected.setGroups({ group });
	//EXPECT_EQ( expected, actual );
}

TEST(OBJFileTest, TestReadGroup )
{
	std::stringstream stream;
	stream
		<< "g front" << std::endl
		<< "f 1 2 3 4" << std::endl
		<< "g back" << std::endl
		<< "f 4 3 2 1" << std::endl;

	OBJFileReader reader;
	OBJFile file = reader.read(stream);
	EXPECT_EQ(3, file.getGroups().size() );

	/*
	std::vector< OBJGroup > expected = {
		OBJGroup("", {}),
		OBJGroup(" front", { OBJFace({ 1, 2, 3, 4 }) }),
		OBJGroup(" back", { OBJFace({ 4, 3, 2, 1 }) })
	};
	EXPECT_EQ( 3, file.getGroups().size() ) ;
	*/
}

TEST( OBJFileTest, TestReadUseMtl )
{
	std::stringstream stream;
	stream
		<< "mtllib master.mtl" << std::endl
		<< "usemtl wood" << std::endl
		<< "f 1 2 3 4" << std::endl;

	OBJFileReader reader;
	OBJFile file = reader.read(stream);

	EXPECT_EQ(1, file.getGroups().front().getFaces().size());
}


/*
TEST(OBJFileTest, TestWriteNormals)
{
	OBJFileWriter writer;
	OBJGroupSPtr group( new OBJGroup() );
	group->setNormals({ Vector3d<T>(0.5f, 1.0f, 0.0f) });
	std::stringstream stream;
	OBJFile file;
	//stream << file;
	file.setGroups({ group });

	writer.write(stream, file);
	const std::vector< std::string >& strs = writer.getStrs();
	EXPECT_EQ(strs[0], "g ");
	EXPECT_EQ(strs[1], "vn 0.500000 1.000000 0.000000");
}

	/*
	{
		OBJFile file;
		OBJGroup group;
		group.setTexCoords({ Vector3d(0.5f, 0.5f, 0.0f) });
		file.setGroups({ group });
		std::stringstream stream;
		file.write(stream);
		EXPECT_EQ("g \nvt 0.5 0.5 0\n", stream.str());
	}

TEST(OBJFileTest, TestWrite2)
{
	std::stringstream stream;
	OBJFileWriter writer;
	OBJGroupSPtr group( new OBJGroup() );
	Buffer3d<T> buffer({0.1f, 0.2f, 0.3f});
	group->setPositions(buffer);
	OBJFile file;
	file.setGroups({ group });

	writer.write(stream, file);

	const std::vector< std::string >& strs = writer.getStrs();
	EXPECT_EQ( strs[0], "g ");
	EXPECT_EQ( strs[1], "v 0.1000 0.2000 0.3000");
}
*/

TEST(OBJFileTest, TestWriteFaces)
{
	OBJFileWriter writer;
	TriangleMesh mesh;
	auto v1 = mesh.createVertex(Vector3d<float>(0.0, 0.0, 0.0));
	auto v2 = mesh.createVertex(Vector3d<float>(1.0, 0.0, 0.0));
	auto v3 = mesh.createVertex(Vector3d<float>(1.0, 1.0, 0.0));
	mesh.createFace(v1, v2, v3);
	writer.write("../TestFile/IO", "OBJWriteTest.obj", mesh);
}


// from http://www.martinreddy.net/gfx/3d/OBJ.spec
TEST(OBJFileTest, TestExampleSquare)
{
	std::stringstream stream;
	stream
		<< "v 0.000000 2.000000 0.000000" << std::endl
		<< "v 0.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 2.000000 0.000000" << std::endl
		<< "f 1 2 3 4" << std::endl;
}

TEST(OBJFileTest, TestExampleCube)
{
	std::stringstream stream;
	stream
		<< "v 0.000000 2.000000 2.000000" << std::endl
		<< "v 0.000000 0.000000 2.000000" << std::endl
		<< "v 2.000000 0.000000 2.000000" << std::endl
		<< "v 2.000000 2.000000 2.000000" << std::endl
		<< "v 0.000000 2.000000 0.000000" << std::endl
		<< "v 0.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 2.000000 0.000000" << std::endl
		<< "f 1 2 3 4" << std::endl
		<< "f 8 7 6 5" << std::endl
		<< "f 4 3 7 8" << std::endl
		<< "f 5 1 4 8" << std::endl
		<< "f 5 6 2 1" << std::endl
		<< "f 2 6 7 3" << std::endl;

	OBJFileReader reader;
	const OBJFile& file = reader.read(stream);
	EXPECT_EQ(1, file.getGroups().size());
	EXPECT_EQ(24, file.getGroups().front().getPositions().get().size());
	EXPECT_EQ(6, file.getGroups().front().getFaces().size());
}

TEST(OBJFileTest, TestNegativeReferenceNumber)
{
	std::stringstream stream;
	stream
		<< "v 0.000000 2.000000 2.000000" << std::endl
		<< "v 0.000000 0.000000 2.000000" << std::endl
		<< "v 2.000000 0.000000 2.000000" << std::endl
		<< "v 2.000000 2.000000 2.000000" << std::endl
		<< "f -4 -3 -2 -1" << std::endl;

	OBJFileReader reader;
	const OBJFile& file = reader.read(stream);
	EXPECT_EQ(1, file.getGroups().size());
	EXPECT_EQ(12, file.getGroups().front().getPositions().get().size());
	EXPECT_EQ(1, file.getGroups().front().getFaces().size());
	std::vector<int> expected{ -4, - 3, -2, -1 };
	EXPECT_EQ(expected, file.getGroups().front().getFaces().front().getVertexIndices());
}

TEST(OBJFileTest, TestExampleGroups)
{
	std::stringstream stream;
	stream
		<< "v 0.000000 2.000000 2.000000" << std::endl
		<< "v 0.000000 0.000000 2.000000" << std::endl
		<< "v 2.000000 0.000000 2.000000" << std::endl
		<< "v 2.000000 2.000000 2.000000" << std::endl
		<< "v 0.000000 2.000000 0.000000" << std::endl
		<< "v 0.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 2.000000 0.000000" << std::endl
		<< "# 8 vertices" << std::endl
		<< "g front cube" << std::endl
		<< "f 1 2 3 4" << std::endl
		<< "g back cube" << std::endl
		<< "f 8 7 6 5" << std::endl
		<< "g right cube" << std::endl
		<< "f 4 3 7 8" << std::endl
		<< "g top cube" << std::endl
		<< "f 5 1 4 8" << std::endl
		<< "g left cube" << std::endl
		<< "f 5 6 2 1" << std::endl
		<< "g bottom cube" << std::endl
		<< "f 2 6 7 3" << std::endl
		<< "# 6 elements" << std::endl;

	OBJFileReader reader;
	const OBJFile& file = reader.read(stream);
	EXPECT_EQ( 7, file.getGroups().size() );
}

TEST(OBJFileTest, TestExampleSmoothingGroup)
{
	std::stringstream stream;
	stream
		<< "v 0.000000 2.000000 0.000000" << std::endl
		<< "v 0.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 2.000000 0.000000" << std::endl
		<< "v 4.000000 0.000000 -1.255298" << std::endl
		<< "v 4.000000 2.000000 -1.255298" << std::endl
		<< "# 6 vertices" << std::endl
		<< "g all" << std::endl
		<< "s 1" << std::endl
		<< "f 1 2 3 4" << std::endl
		<< "f 4 3 5 6" << std::endl
		<< "# 2 elements" << std::endl;

	OBJFileReader reader;
	const OBJFile& file = reader.read(stream);
	EXPECT_EQ(2, file.getGroups().size());
	EXPECT_EQ(18, file.getGroups().front().getPositions().get().size());
	EXPECT_EQ(2, file.getGroups().back().getFaces().size());
}

TEST(OBJFileTest, TestExampleTextureMappedSquare)
{
	std::stringstream stream;
	stream
		<< "mtllib master.mtl" << std::endl
		<< "v 0.000000 2.000000 0.000000" << std::endl
		<< "v 0.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 0.000000 0.000000" << std::endl
		<< "v 2.000000 2.000000 0.000000" << std::endl
		<< "vt 0.000000 1.000000 0.000000" << std::endl
		<< "vt 0.000000 0.000000 0.000000" << std::endl
		<< "vt 1.000000 0.000000 0.000000" << std::endl
		<< "vt 1.000000 1.000000 0.000000" << std::endl
		<< "# 4 vertices" << std::endl
		<< "usemtl wood" << std::endl
		<< "f 1/1 2/2 3/3 4/4" << std::endl
		<< "# 1 element" << std::endl;

	OBJFileReader reader;
	const OBJFile& file = reader.read(stream);
	EXPECT_EQ(1, file.getGroups().size());
	EXPECT_EQ(12, file.getGroups().front().getPositions().get().size());
	EXPECT_EQ(12, file.getGroups().front().getTexCoords().get().size());
}