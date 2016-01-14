#include "gtest/gtest.h"

#include "CGBFile.h"
#include <vector>
#include <string>
#include <fstream>



using namespace tinyxml2;
using namespace Crystal::Math;
using namespace Crystal::IO;

using GeomType = float;
using ValueType = float;

TEST(CGBFileTest, TestSave)
{
	CGBFile<GeomType, ValueType> file;
	Space3d<GeomType> space;
	Grid3d<ValueType> grid(2,2,2);
	grid.set(0, 0, 0, 1.0f);
	Volume3d<GeomType, ValueType> v(space, grid);
	EXPECT_EQ( tinyxml2::XML_NO_ERROR, file.save("../TestFile/IO/CGB","CGBTestFileSave.xml", v) );
	//EXPECT_EQ( 2, file.getImageFileNames().size() );
}

TEST(CGBFileTest, TestSaveInvalid)
{
	CGBFile<GeomType, ValueType> file;
	Space3d<GeomType> space;
	Grid3d<ValueType> grid(2, 2, 2);
	grid.set(0, 0, 0, 1.0f);
	Volume3d<GeomType, ValueType> v(space, grid);
	EXPECT_EQ( tinyxml2::XML_ERROR_FILE_COULD_NOT_BE_OPENED, file.save("../TestFile/IO", "", v));
}

TEST(CGBFileTest, TestLoad)
{
	CGBFile<GeomType, ValueType> file;
	EXPECT_EQ( tinyxml2::XML_NO_ERROR, file.load("../TestFile/IO/CGB", "CGBTestFileLoad.xml") );

	const auto actual = file.getVolume();
	const Space3d<GeomType> space;
	Grid3d<ValueType> grid(2,2,2);
	grid.set(0, 0, 0, 1.0f);
	const Volume3d<GeomType, ValueType> expected(space, grid);

	EXPECT_EQ(expected, actual);

	//EXPECT_EQ(2, file.getImageFileNames().size());

}

TEST(CGBFileTest, TestLoadInvalid)
{
	CGBFile<GeomType, ValueType> file;
	EXPECT_EQ(tinyxml2::XML_ERROR_FILE_NOT_FOUND, file.load("../TestFile/IO", ""));
}
