#include "gtest/gtest.h"
#include "../IO/File.h"

using namespace Crystal::IO;


TEST(FileTest, TestGetFileName)
{
	File file("test.txt");
	EXPECT_EQ("test", file.getFileName());
}

TEST(FileTest, TestGetExtension)
{
	File file("test.txt");
	EXPECT_EQ("txt", file.getExtension());
}
