#include "gtest\gtest.h"
#include "../Graphics/DrawableID.h"
#include "../Graphics/ColorRGBA.h"

using namespace Crystal::Graphics;

TEST(DrawableIDTest, TestFromColor)
{
	EXPECT_EQ(DrawableID(0), DrawableID(ColorRGBA<float>(0, 0, 0, 0)));
	EXPECT_EQ(DrawableID(30), DrawableID(ColorRGBA<float>(30.0f / 256.0f, 0, 0, 0)));
	EXPECT_EQ(DrawableID(256), DrawableID(ColorRGBA<float>(0, 1.0f/256.0f, 0, 0)));
	EXPECT_EQ(DrawableID(256*256), DrawableID(ColorRGBA<float>(0, 0, 1.0f / 256.0f, 0)));
}

TEST(DrawableIDTest, TestFromColorUC)
{
	EXPECT_EQ(DrawableID(0), DrawableID(ColorRGBA<unsigned char>(0, 0, 0, 0)));
	EXPECT_EQ(DrawableID(30), DrawableID(ColorRGBA<unsigned char>(30, 0, 0, 0)));
	EXPECT_EQ(DrawableID(256), DrawableID(ColorRGBA<unsigned char>(0, 1, 0, 0)));
	EXPECT_EQ(DrawableID(256 * 256), DrawableID(ColorRGBA<unsigned char>(0, 0, 1, 0)));
}


TEST(DrawableIDTest, TestToColor)
{
	EXPECT_EQ(ColorRGBA<float>(0.0f, 0.0f, 0.0f, 1.0f), DrawableID(0).toColor());
	EXPECT_EQ(ColorRGBA<float>(30.0f / 256.0f, 0.0f, 0.0f, 1.0f), DrawableID(30).toColor());
	EXPECT_EQ(ColorRGBA<float>(0.0f, 1.0f / 256.0f, 0.0f, 1.0f), DrawableID(256).toColor());
	EXPECT_EQ(ColorRGBA<float>(0.0f, 0.0f, 1.0f / 256.0f, 1.0f), DrawableID(256 * 256).toColor());
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