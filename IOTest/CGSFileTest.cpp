#include "gtest\gtest.h"
#include "../IO/CGSFile.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

TEST(CGSFileTest, TestSave)
{
	CGSFile file;

	Grid3d<float> grid(2,2,2);
	EXPECT_TRUE( file.save("../TestFile/IO/CGSFileWrite.cgs", grid) );
}

TEST(CGSFileTest, TestLoad)
{
	CGSFile file;

	EXPECT_TRUE(file.load("../TestFile/IO/CGSFileRead.cgs"));
	//file.getVolume();
}