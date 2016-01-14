#include "gtest/gtest.h"
#include "../IO/MetaLanguage.h"

using namespace Crystal::IO;

TEST(MetaLanguageTest, Test)
{
	MetaLanguage meta("HELLO");
	EXPECT_EQ("HELLO",meta.toStdString());
}