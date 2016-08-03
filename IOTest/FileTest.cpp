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

TEST(FileTest, TestGetFolderPath)
{
	{
		const File file("../Sample/Test.txt");
		EXPECT_EQ("../Sample/", file.getFolderPath());
	}
	{
		const File file("..\\Sample\\Test.txt");
		EXPECT_EQ("..\\Sample\\", file.getFolderPath());
	}

}

TEST(FileTest, TestGetFileNameExcludingPath)
{
	File file("../Sample/Test.txt");
	EXPECT_EQ("Test.txt", file.getFileNameExcludingPath());
}