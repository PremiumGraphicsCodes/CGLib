#include "gtest/gtest.h"

#include "../Core/PolygonMesh.h"
#include "../IO/MTLFile.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;

::std::ostream& operator<<(::std::ostream& os, const ColorRGBA<float>& c) {
	return os << c.getRed() << c.getGreen() << c.getBlue() << std::endl;
}


::std::ostream& operator<<(::std::ostream& os, const OBJMaterial& mtl) {
	return os << mtl.getAmbient() << mtl.getDiffuse() << mtl.getSpecular() << std::endl;
}

TEST(MTLFileReaderTest, TestRead)
{
	std::stringstream stream;
	stream
		<< "newmtl FrontColor" << std::endl
		<< "Ka 0.0 0.0 0.0" << std::endl
		<< "Kd 1.0 1.0 1.0" << std::endl
		<< "Ks 0.1 0.1 0.1" << std::endl
		<< "illum 0" << std::endl;

	MTLFile file;
	EXPECT_TRUE( file.read(stream) );
	
	OBJMaterial expected;
	expected.setName( "FrontColor" );
	expected.setAmbient( ColorRGBA<float>(0.0f, 0.0f, 0.0f) );
	expected.setDiffuse( ColorRGBA<float>(1.0f, 1.0f, 1.0f) );
	expected.setSpecular( ColorRGBA<float>(0.1f, 0.1f, 0.1f) );

	const std::vector<OBJMaterial> expecteds = { expected };
	EXPECT_EQ( expecteds, file.materials);
}

TEST(MTLFileReaderTest, TestReadTexture)
{
	std::stringstream stream;
	stream
		<< "newmtl name" << std::endl
		<< "map_Ka ambient.png" << std::endl
		<< "map_Kd diffuse.png" << std::endl
		<< "map_Ks shininess.png" << std::endl
		<< "bump bump.png" << std::endl;

	MTLFile file;
	EXPECT_TRUE( file.read(stream) );

	OBJMaterial expected;
	expected.setName( "name" );
	expected.setAmbientTextureName( "ambient.png" );
	expected.setDiffuseTextureName( "diffuse.png" );
	expected.setShininessTextureName( "shininess.png" );
	expected.setBumpTextureName( "bump.png" );

	const std::vector<OBJMaterial> expecteds = { expected };
	EXPECT_EQ(expecteds, file.materials);
}


// from http://paulbourke.net/dataformats/mtl/
TEST(MTLFileReaderTest, TestExample1)
{
	std::stringstream stream;
	stream
		<< "newmtl neon_green" << std::endl
		<< "Kd 0.0000 1.0000 0.0000" << std::endl
		<< "illum 0" << std::endl;

	MTLFile file;
	EXPECT_TRUE(file.read(stream));
	EXPECT_EQ( 1, file.materials.size() );
	EXPECT_EQ("neon_green", file.materials.front().getName());
	EXPECT_EQ( ColorRGBA<float>(0.0, 1.0, 0.0), file.materials.front().getDiffuse() );
	EXPECT_EQ(0, file.materials.front().getIllumination());
}

TEST(MTLFileReaderTest, TestExample2)
{
	std::stringstream stream;
	stream
		<< "newmtl flat_green" << std::endl
		<< "Ka 0.0000 1.0000 0.0000" << std::endl
		<< "Kd 0.0000 1.0000 0.0000" << std::endl
		<< "illum 1" << std::endl;
	MTLFile file;
	EXPECT_TRUE(file.read(stream));

	EXPECT_EQ(1, file.materials.size());
	EXPECT_EQ("flat_green", file.materials.front().getName());
	EXPECT_EQ(ColorRGBA<float>(0.0, 1.0, 0.0), file.materials.front().getAmbient());
	EXPECT_EQ(ColorRGBA<float>(0.0, 1.0, 0.0), file.materials.front().getDiffuse());
	EXPECT_EQ(1, file.materials.front().getIllumination());

}

TEST(MTLFileReaderTest, TestExample3)
{
	std::stringstream stream;
	stream
		<< "newmtl diss_green" << std::endl
		<< "Ka 0.0000 1.0000 0.0000" << std::endl
		<< "Kd 0.0000 1.0000 0.0000" << std::endl
		<< "d 0.8000" << std::endl
		<< "illum 1" << std::endl;

	MTLFile file;
	EXPECT_TRUE(file.read(stream));
	EXPECT_EQ(1, file.materials.size());

	const OBJMaterial& mtl = file.materials.front();
	EXPECT_EQ("diss_green", mtl.getName());
	EXPECT_EQ(ColorRGBA<float>(0.0, 1.0, 0.0), mtl.getAmbient());
	EXPECT_EQ(ColorRGBA<float>(0.0, 1.0, 0.0), mtl.getDiffuse());
	EXPECT_FLOAT_EQ(0.8f, mtl.getTransparent());
	EXPECT_EQ(1, mtl.getIllumination());
}

TEST(MTLFileReaderTest, TestExample4)
{
	std::stringstream stream;
	stream
		<< "newmtl shiny_green" << std::endl
		<< "Ka 0.0000 1.0000 0.0000" << std::endl
		<< "Kd 0.0000 1.0000 0.0000" << std::endl
		<< "Ks 1.0000 1.0000 1.0000" << std::endl
		<< "Ns 200.0000" << std::endl
		<< "illum 1" << std::endl;

	MTLFile file;
	EXPECT_TRUE(file.read(stream));
	EXPECT_EQ(1, file.materials.size());

	const OBJMaterial& mtl = file.materials.front();
	EXPECT_EQ("shiny_green", mtl.getName());
	EXPECT_EQ(ColorRGBA<float>(0.0, 1.0, 0.0), mtl.getAmbient());
	EXPECT_EQ(ColorRGBA<float>(0.0, 1.0, 0.0), mtl.getDiffuse());
	EXPECT_EQ(ColorRGBA<float>(1.0, 1.0, 1.0), mtl.getSpecular());
	EXPECT_FLOAT_EQ(200.0f, mtl.getSpecularExponent());
	EXPECT_EQ(1, mtl.getIllumination());
}

TEST(MTLFileReaderTest, TestExample5)
{
	std::stringstream stream;
	stream
		<< "newmtl green_mirror" << std::endl
		<< "Ka 0.0000 1.0000 0.0000" << std::endl
		<< "Kd 0.0000 1.0000 0.0000" << std::endl
		<< "Ks 0.0000 1.0000 0.0000" << std::endl
		<< "Ns 200.0000" << std::endl
		<< "illum 3" << std::endl;

	MTLFile file;
	EXPECT_TRUE(file.read(stream));

	EXPECT_EQ(1, file.materials.size());
	const OBJMaterial& mtl = file.materials.front();
	EXPECT_EQ("green_mirror", mtl.getName());
	EXPECT_EQ(ColorRGBA<float>(0.0, 1.0, 0.0), mtl.getAmbient());
	EXPECT_EQ(ColorRGBA<float>(0.0, 1.0, 0.0), mtl.getDiffuse());
	EXPECT_EQ(ColorRGBA<float>(0.0, 1.0, 0.0), mtl.getSpecular());
	EXPECT_FLOAT_EQ(200.0f, mtl.getSpecularExponent());
	EXPECT_EQ(3, mtl.getIllumination());
}

TEST(MTLFileReaderTest, TestExample6)
{
	std::stringstream stream;
	stream
		<< "newmtl fake_windsh" << std::endl
		<< "Ka 0.0000 0.0000 0.0000" << std::endl
		<< "Kd 0.0000 0.0000 0.0000" << std::endl
		<< "Ks 0.9000 0.9000 0.9000" << std::endl
		<< "d 0.1000" << std::endl
		<< "Ns 200" << std::endl
		<< "illum 4" << std::endl;

	MTLFile file;
	EXPECT_TRUE(file.read(stream));
	EXPECT_EQ(1, file.materials.size());
	const OBJMaterial& mtl = file.materials.front();
	EXPECT_EQ("fake_windsh", mtl.getName());
	EXPECT_EQ(ColorRGBA<float>(0.0, 0.0, 0.0), mtl.getAmbient());
	EXPECT_EQ(ColorRGBA<float>(0.0, 0.0, 0.0), mtl.getDiffuse());
	EXPECT_EQ(ColorRGBA<float>(0.9f, 0.9f, 0.9f), mtl.getSpecular());
	EXPECT_FLOAT_EQ(200.0f, mtl.getSpecularExponent());
	EXPECT_EQ(4, mtl.getIllumination());
}

TEST(MTLFileReaderTest, TestExample7)
{
	std::stringstream stream;
	stream
		<< "newmtl fresnel_blue" << std::endl
		<< "Ka 0.0000 0.0000 0.0000" << std::endl
		<< "Kd 0.0000 0.0000 0.0000" << std::endl
		<< "Ks 0.6180 0.8760 0.1430" << std::endl
		<< "Ns 200" << std::endl
		<< "illum 5" << std::endl;

	MTLFile file;
	EXPECT_TRUE(file.read(stream));
	EXPECT_EQ(1, file.materials.size());
	const OBJMaterial& mtl = file.materials.front();
	EXPECT_EQ("fresnel_blue", mtl.getName());
	EXPECT_EQ(ColorRGBA<float>(0.0f, 0.0f, 0.0f), mtl.getAmbient());
	EXPECT_EQ(ColorRGBA<float>(0.0f, 0.0f, 0.0f), mtl.getDiffuse());
	EXPECT_EQ(ColorRGBA<float>(0.6180f, 0.8760f, 0.1430f), mtl.getSpecular());
	EXPECT_FLOAT_EQ(200.0f, mtl.getSpecularExponent());
	EXPECT_EQ(5, mtl.getIllumination());
}

TEST(MTLFileReaderTest, TestExample8)
{
	std::stringstream stream;
	stream
		<< "newmtl real_windsh" << std::endl
		<< "Ka 0.0000 0.0000 0.0000" << std::endl
		<< "Kd 0.0000 0.0000 0.0000" << std::endl
		<< "Ks 0.0000 0.0000 0.0000" << std::endl
		<< "Tf 1.0000 1.0000 1.0000" << std::endl
		<< "Ns 200" << std::endl
		<< "Ni 1.2000" << std::endl
		<< "illum 6" << std::endl;

	MTLFile file;
	EXPECT_TRUE(file.read(stream));
	EXPECT_EQ(1, file.materials.size());
	const OBJMaterial& mtl = file.materials.front();
	EXPECT_EQ("real_windsh", mtl.getName());
	EXPECT_FLOAT_EQ(1.2f, mtl.getOpticalDensity());
}

TEST(MTLFileReaderTest, TestReadMaterials)
{
	std::stringstream stream;
	stream
		<< "newmtl mat1" << std::endl
		<< "Ka 0.0000 0.0000 0.0000" << std::endl
		<< "Kd 0.0000 0.0000 0.0000" << std::endl
		<< "Ks 0.0000 0.0000 0.0000" << std::endl
		<< "Tf 1.0000 1.0000 1.0000" << std::endl
		<< "Ns 200" << std::endl
		<< "Ni 1.2000" << std::endl
		<< "illum 6" << std::endl
		<< "newmtl mat2" << std::endl
		<< "Ka 0.0000 0.0000 0.0000" << std::endl
		<< "Kd 0.0000 0.0000 0.0000" << std::endl
		<< "Ks 0.0000 0.0000 0.0000" << std::endl
		<< "Tf 1.0000 1.0000 1.0000" << std::endl
		<< "Ns 200" << std::endl
		<< "Ni 1.2000" << std::endl
		<< "illum 6" << std::endl;

	MTLFile file;
	EXPECT_TRUE(file.read(stream));
	EXPECT_EQ(2, file.materials.size());
	const OBJMaterial& mtl = file.materials.front();
	EXPECT_EQ("mat1", mtl.getName());
	EXPECT_FLOAT_EQ(1.2f, mtl.getOpticalDensity());
	const OBJMaterial& mtl2 = file.materials.back();
	EXPECT_EQ("mat2", mtl2.getName());

}