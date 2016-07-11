#include "stdafx.h"
/*
#include "../Core/UID.h"

using namespace Crystal::Core;

TEST(UIDTest, TestGetType)
{
	EXPECT_EQ(UID::Type::Surface, UID(0, UID::Type::Surface).getType());
	EXPECT_EQ(UID::Type::Surface, UID(1, UID::Type::Surface).getType());
	EXPECT_EQ(UID::Type::Vertex, UID(0, UID::Type::Vertex).getType());
	EXPECT_EQ(UID::Type::Glyph, UID(0, UID::Type::Glyph).getType());

}

TEST(UIDTest, TestGetID)
{
	EXPECT_EQ(0, UID(0, UID::Type::Surface).getID());
	EXPECT_EQ(50, UID(50, UID::Type::Surface).getID());

	EXPECT_EQ(0, UID(0, UID::Type::Vertex).getID());
}

TEST(UIDTest, TestToInt)
{
	EXPECT_EQ(0, UID(0, 0).toInt());
	std::bitset<32> expected;
	//expected.set(32-8, true);
	EXPECT_EQ(std::pow(2,24), UID(0, 1).toInt());
	EXPECT_EQ(std::pow(2,25), UID(0, 2).toInt());
	EXPECT_EQ(std::pow(2,25)+std::pow(2,24), UID(0, 3).toInt());

}
*/