#include "gtest\gtest.h"
#include "../Graphics/DrawableID.h"
#include "../Graphics/ColorRGBA.h"

using namespace Crystal::Graphics;

TEST(DrawableIDTest, TestToColor)
{
	{
		DrawableID id(0);
		const auto& actual = id.toColor();
		ColorRGBA<float> expected(0.0f, 0.0f, 0.0f, 1.0f);
		EXPECT_EQ(expected, actual);
	}

	{
		DrawableID id(30);
		const auto& actual = id.toColor();
		ColorRGBA<float> expected(30.0f / 255.0f, 0.0f, 0.0f, 1.0f);
		EXPECT_EQ(expected, actual);
	}

	{
		DrawableID id(255);
		const auto& actual = id.toColor();
		ColorRGBA<float> expected(0.0f, 1.0f/255.0f, 0.0f, 1.0f);
		EXPECT_EQ(expected, actual);
	}
	{
		DrawableID id(255*255);
		const auto& actual = id.toColor();
		ColorRGBA<float> expected(0.0f, 0.0f, 1.0f / 255.0f, 1.0f);
		EXPECT_EQ(expected, actual);
	}

}


/*
TEST(ColorRGBATest, TestConstruct)
{
const ColorRGBA<unsigned char> c(30);
EXPECT_EQ(0, c.getRed());
EXPECT_EQ(30, c.getGreen());
EXPECT_EQ(0, c.getBlue());
EXPECT_EQ(255, c.getAlpha());
EXPECT_EQ(30, c.toUInt());
}
*/