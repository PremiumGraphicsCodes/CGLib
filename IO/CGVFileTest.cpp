#include "gtest\gtest.h"
#include "../IO/CGVFile.h"

using namespace Crystal::Math;
using namespace Crystal::IO;

TEST(CGVFileTest, TestSave)
{
	CGVFile file;

	Grid3d<float> grid(2, 2, 2);
	grid.fill(0);
	Space3d<float> space;
	Volume3d<float, float> volume(space, grid);
	EXPECT_TRUE(file.save("../TestFile/IO/CGVFileWrite.cgs", volume));

	EXPECT_TRUE( file.load("../TestFile/IO/CGVFileWrite.cgs"));

	const auto& actual = file.getVolume();
	EXPECT_EQ(volume, actual);
}