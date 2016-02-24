#include "gtest\gtest.h"
#include "../IO/VMDFile.h"

using namespace Crystal::IO;

TEST(VMDFileTest, TestWrite)
{
	VMDFile file;
	file.write("../TestFile/IO/VMDFileWriteTest.vmd");
}