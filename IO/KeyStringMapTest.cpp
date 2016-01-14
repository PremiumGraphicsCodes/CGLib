#include "gtest/gtest.h"

#include "StringTable.h"

using namespace Crystal::IO;

TEST(KeyStringMapTest, TestWrite)
{
	KeyStringMap map;
	map.add("ID_HELLO", "Ç±ÇÒÇ…ÇøÇÕ");
	map.add("ID_EXIT", "èIóπ");
	const auto file = Crystal::File("../TestFile/IO/StringTable/WriteKeyStringMap.txt");
	EXPECT_TRUE( map.write(file) );
}

TEST(KeyStringMapTest, TestWriteInvalid)
{
	KeyStringMap map;
	const auto file = Crystal::File("../TestFile/IO/StringTable/");
	EXPECT_FALSE(map.write(file));
}


TEST(KeyStringMapTest, TestRead)
{
	KeyStringMap map;
	const auto file = Crystal::File("../TestFile/IO/StringTable/ReadKeyStringMap.txt");
	EXPECT_TRUE( map.read(file) );
	EXPECT_EQ("Ç±ÇÒÇ…ÇøÇÕ", map.get("ID_HELLO"));
	EXPECT_EQ("èIóπ", map.get("ID_EXIT"));
}

TEST(KeyStringMapTest, TestReadInvalid)
{
	KeyStringMap map;
	const auto file = Crystal::File("../TestFile/IO/StringTable/");
	EXPECT_FALSE( map.read(file) );
}
