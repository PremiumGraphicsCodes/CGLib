#include "gtest/gtest.h"
 
#include "../IO/MTLFile.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::IO;

using T = float;

TEST(MTLTextureOptionTest, TestConstruct)
{
	MTLTextureOption opt;

	EXPECT_TRUE( opt.getBlendU() );
	EXPECT_TRUE( opt.getBlendV() );
	EXPECT_EQ( Vector3d<T>(0.0f, 0.0f, 0.0f), opt.getOrigin() );
	EXPECT_EQ( Vector3d<T>(1.0f, 1.0f, 1.0f), opt.getScale() );
	EXPECT_EQ( 0.0, opt.getBaseValue() );
	EXPECT_EQ( 1.0, opt.getGainValue() );
	EXPECT_EQ( "l", opt.getImfChan() );
}

TEST(MTLFileTest, TestWriteTextureOptions)
{
	MTLTextureOption opt;
	MTLFile file;
	std::ostringstream stream;
	const std::vector< std::string >& strs = file.writeTextureOptions(stream, opt);
	EXPECT_EQ(strs[0], "-blendu on");
	EXPECT_EQ(strs[1], "-blendv on");
}

TEST(MTLFileTest, TestReadTextureOptions)
{
	EXPECT_TRUE( MTLFile::getTextureOptions("-blendu on").getBlendU() );
	EXPECT_TRUE( MTLFile::getTextureOptions("-blendv on").getBlendV() );

	EXPECT_FALSE( MTLFile::getTextureOptions("-blendu off").getBlendU() );
	EXPECT_FALSE( MTLFile::getTextureOptions("-blendv off").getBlendV() );

	EXPECT_FLOAT_EQ( 0.1f, MTLFile::getTextureOptions("-boost 0.1").getBoost() );

	EXPECT_FLOAT_EQ( 0.1f, MTLFile::getTextureOptions("-mm 0.1 0.5").getBaseValue() );

	EXPECT_EQ( Vector3d<T>(1.0f, 0.0f, 0.0f), MTLFile::getTextureOptions("-o 1.0 0.0 0.0").getOrigin() );
	EXPECT_EQ( Vector3d<T>(0.1f, 0.1f, 0.1f), MTLFile::getTextureOptions("-s 0.1 0.1 0.1").getScale() );
	EXPECT_EQ( Vector3d<T>(0.5f, 0.5f, 0.0f), MTLFile::getTextureOptions("-t 0.5 0.5 0.0").getTurblence() );

	EXPECT_EQ( 255, MTLFile::getTextureOptions("-texres 255").getResolution() );

	EXPECT_TRUE( MTLFile::getTextureOptions("-clamp on").getClamp() );
	EXPECT_FALSE( MTLFile::getTextureOptions("-clamp off").getClamp() );

	EXPECT_EQ( "r", MTLFile::getTextureOptions("-imfchan r").getImfChan() );
	EXPECT_EQ( "g", MTLFile::getTextureOptions("-imfchan g").getImfChan() );
	EXPECT_EQ( "b", MTLFile::getTextureOptions("-imfchan b").getImfChan() );
	EXPECT_EQ( "m", MTLFile::getTextureOptions("-imfchan m").getImfChan() );
	EXPECT_EQ( "l", MTLFile::getTextureOptions("-imfchan l").getImfChan() );
	EXPECT_EQ( "z", MTLFile::getTextureOptions("-imfchan z").getImfChan() );

	EXPECT_EQ("rgb", MTLFile::getTextureOptions("-imfchan rgb").getImfChan());

	EXPECT_EQ("cube_top", MTLFile::getTextureOptions("-type cube_top").getType());
}


::std::ostream& operator<<(::std::ostream& os, const ColorRGB<float>& c) {
	return os << c.getRed() << c.getGreen() << c.getBlue() << std::endl;
}


::std::ostream& operator<<(::std::ostream& os, const MTL& mtl) {
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

	MTLFileReader reader;
	const MTLFile& file = reader.read(stream);
	
	MTL expected;
	expected.setName( "FrontColor" );
	expected.setAmbient( ColorRGB<float>(0.0f, 0.0f, 0.0f) );
	expected.setDiffuse( ColorRGB<float>(1.0f, 1.0f, 1.0f) );
	expected.setSpecular( ColorRGB<float>(0.1f, 0.1f, 0.1f) );

	const std::vector<MTL> expecteds = { expected };
	EXPECT_EQ( expecteds, file.mtls);
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

	MTLFileReader reader;
	const MTLFile& file = reader.read(stream);

	MTL expected;
	expected.setName( "name" );
	expected.setAmbientTextureName( "ambient.png" );
	expected.setDiffuseTextureName( "diffuse.png" );
	expected.setShininessTextureName( "shininess.png" );
	expected.setBumpTextureName( "bump.png" );

	const std::vector<MTL> expecteds = { expected };
	EXPECT_EQ(expecteds, file.mtls);
}


TEST(MTLFileWriterTest, TestWrite)
{
	Material m(0);
	m.setAmbient(ColorRGBA<float>(1.0f, 1.0f, 1.0f));
	m.setDiffuse(ColorRGBA<float>(1.0f, 0.0f, 0.0f));
	m.setSpecular(ColorRGBA<float>(0.0f, 0.0f, 1.0f));
	m.setShininess(10.0f);
	m.setTransparent(0.9f);

	std::ostringstream stream;
	MTLFileWriter writer;
	writer.save(stream, m);
	const std::vector< std::string >& strs = writer.getStrs();
	EXPECT_EQ("Ka 1.0000 1.0000 1.0000", strs.front());
	EXPECT_EQ("Kd 1.0000 0.0000 0.0000", strs[1]);
	EXPECT_EQ("Ks 0.0000 0.0000 1.0000", strs[2]);
	EXPECT_EQ("Ns 10.0000", strs[3]);
	EXPECT_EQ("Tr 0.9000", strs[4]);
	//const std::string& str = stream.str();
}

// from http://paulbourke.net/dataformats/mtl/
TEST(MTLFileReaderTest, TestExample1)
{
	MTLFileReader reader;
	std::stringstream stream;
	stream
		<< "newmtl neon_green" << std::endl
		<< "Kd 0.0000 1.0000 0.0000" << std::endl
		<< "illum 0" << std::endl;

	const MTLFile& file = reader.read(stream);
	EXPECT_EQ( 1, file.mtls.size() );
	EXPECT_EQ("neon_green", file.mtls.front().getName());
	EXPECT_EQ( ColorRGB<float>(0.0, 1.0, 0.0), file.mtls.front().getDiffuse() );
	EXPECT_EQ(0, file.mtls.front().getIllumination());
}

TEST(MTLFileReaderTest, TestExample2)
{
	MTLFileReader reader;
	std::stringstream stream;
	stream
		<< "newmtl flat_green" << std::endl
		<< "Ka 0.0000 1.0000 0.0000" << std::endl
		<< "Kd 0.0000 1.0000 0.0000" << std::endl
		<< "illum 1" << std::endl;
	const MTLFile& file = reader.read(stream);
	EXPECT_EQ(1, file.mtls.size());
	EXPECT_EQ("flat_green", file.mtls.front().getName());
	EXPECT_EQ(ColorRGB<float>(0.0, 1.0, 0.0), file.mtls.front().getAmbient());
	EXPECT_EQ(ColorRGB<float>(0.0, 1.0, 0.0), file.mtls.front().getDiffuse());
	EXPECT_EQ(1, file.mtls.front().getIllumination());

}

TEST(MTLFileReaderTest, TestExample3)
{
	MTLFileReader reader;
	std::stringstream stream;
	stream
		<< "newmtl diss_green" << std::endl
		<< "Ka 0.0000 1.0000 0.0000" << std::endl
		<< "Kd 0.0000 1.0000 0.0000" << std::endl
		<< "d 0.8000" << std::endl
		<< "illum 1" << std::endl;

	const MTLFile& file = reader.read(stream);
	EXPECT_EQ(1, file.mtls.size());

	const MTL& mtl = file.mtls.front();
	EXPECT_EQ("diss_green", mtl.getName());
	EXPECT_EQ(ColorRGB<float>(0.0, 1.0, 0.0), mtl.getAmbient());
	EXPECT_EQ(ColorRGB<float>(0.0, 1.0, 0.0), mtl.getDiffuse());
	EXPECT_FLOAT_EQ(0.8f, mtl.getTransparent());
	EXPECT_EQ(1, mtl.getIllumination());
}

TEST(MTLFileReaderTest, TestExample4)
{
	MTLFileReader reader;
	std::stringstream stream;
	stream
		<< "newmtl shiny_green" << std::endl
		<< "Ka 0.0000 1.0000 0.0000" << std::endl
		<< "Kd 0.0000 1.0000 0.0000" << std::endl
		<< "Ks 1.0000 1.0000 1.0000" << std::endl
		<< "Ns 200.0000" << std::endl
		<< "illum 1" << std::endl;

	const MTLFile& file = reader.read(stream);
	EXPECT_EQ(1, file.mtls.size());

	const MTL& mtl = file.mtls.front();
	EXPECT_EQ("shiny_green", mtl.getName());
	EXPECT_EQ(ColorRGB<float>(0.0, 1.0, 0.0), mtl.getAmbient());
	EXPECT_EQ(ColorRGB<float>(0.0, 1.0, 0.0), mtl.getDiffuse());
	EXPECT_EQ(ColorRGB<float>(1.0, 1.0, 1.0), mtl.getSpecular());
	EXPECT_FLOAT_EQ(200.0f, mtl.getSpecularExponent());
	EXPECT_EQ(1, mtl.getIllumination());
}

TEST(MTLFileReaderTest, TestExample5)
{
	MTLFileReader reader;
	std::stringstream stream;
	stream
		<< "newmtl green_mirror" << std::endl
		<< "Ka 0.0000 1.0000 0.0000" << std::endl
		<< "Kd 0.0000 1.0000 0.0000" << std::endl
		<< "Ks 0.0000 1.0000 0.0000" << std::endl
		<< "Ns 200.0000" << std::endl
		<< "illum 3" << std::endl;

	const MTLFile& file = reader.read(stream);

	EXPECT_EQ(1, file.mtls.size());
	const MTL& mtl = file.mtls.front();
	EXPECT_EQ("green_mirror", mtl.getName());
	EXPECT_EQ(ColorRGB<float>(0.0, 1.0, 0.0), mtl.getAmbient());
	EXPECT_EQ(ColorRGB<float>(0.0, 1.0, 0.0), mtl.getDiffuse());
	EXPECT_EQ(ColorRGB<float>(0.0, 1.0, 0.0), mtl.getSpecular());
	EXPECT_FLOAT_EQ(200.0f, mtl.getSpecularExponent());
	EXPECT_EQ(3, mtl.getIllumination());
}

TEST(MTLFileReaderTest, TestExample6)
{
	MTLFileReader reader;
	std::stringstream stream;
	stream
		<< "newmtl fake_windsh" << std::endl
		<< "Ka 0.0000 0.0000 0.0000" << std::endl
		<< "Kd 0.0000 0.0000 0.0000" << std::endl
		<< "Ks 0.9000 0.9000 0.9000" << std::endl
		<< "d 0.1000" << std::endl
		<< "Ns 200" << std::endl
		<< "illum 4" << std::endl;

	const MTLFile& file = reader.read(stream);
	EXPECT_EQ(1, file.mtls.size());
	const MTL& mtl = file.mtls.front();
	EXPECT_EQ("fake_windsh", mtl.getName());
	EXPECT_EQ(ColorRGB<float>(0.0, 0.0, 0.0), mtl.getAmbient());
	EXPECT_EQ(ColorRGB<float>(0.0, 0.0, 0.0), mtl.getDiffuse());
	EXPECT_EQ(ColorRGB<float>(0.9f, 0.9f, 0.9f), mtl.getSpecular());
	EXPECT_FLOAT_EQ(200.0f, mtl.getSpecularExponent());
	EXPECT_EQ(4, mtl.getIllumination());
}

TEST(MTLFileReaderTest, TestExample7)
{
	MTLFileReader reader;
	std::stringstream stream;
	stream
		<< "newmtl fresnel_blue" << std::endl
		<< "Ka 0.0000 0.0000 0.0000" << std::endl
		<< "Kd 0.0000 0.0000 0.0000" << std::endl
		<< "Ks 0.6180 0.8760 0.1430" << std::endl
		<< "Ns 200" << std::endl
		<< "illum 5" << std::endl;

	const MTLFile& file = reader.read(stream);
	EXPECT_EQ(1, file.mtls.size());
	const MTL& mtl = file.mtls.front();
	EXPECT_EQ("fresnel_blue", mtl.getName());
	EXPECT_EQ(ColorRGB<float>(0.0f, 0.0f, 0.0f), mtl.getAmbient());
	EXPECT_EQ(ColorRGB<float>(0.0f, 0.0f, 0.0f), mtl.getDiffuse());
	EXPECT_EQ(ColorRGB<float>(0.6180f, 0.8760f, 0.1430f), mtl.getSpecular());
	EXPECT_FLOAT_EQ(200.0f, mtl.getSpecularExponent());
	EXPECT_EQ(5, mtl.getIllumination());
}

TEST(MTLFileReaderTest, TestExample8)
{
	MTLFileReader reader;
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

	const MTLFile& file = reader.read(stream);
	EXPECT_EQ(1, file.mtls.size());
	const MTL& mtl = file.mtls.front();
	EXPECT_EQ("real_windsh", mtl.getName());
	EXPECT_FLOAT_EQ(1.2f, mtl.getOpticalDensity());
}