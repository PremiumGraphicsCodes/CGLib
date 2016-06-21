#include "stdafx.h"
#include "../Graphics/DrawableID.h"
#include "../Graphics/ColorRGBA.h"

using namespace Crystal::Core;
using namespace Crystal::Graphics;

TEST(DrawableIDTest, TestFromColor)
{
	EXPECT_EQ(DrawableID(0), DrawableID(ColorRGBA<float>(0, 0, 0, 0)));
	EXPECT_EQ(DrawableID(30), DrawableID(ColorRGBA<float>(30.0f / 256.0f, 0, 0, 0)));
	EXPECT_EQ(DrawableID(256), DrawableID(ColorRGBA<float>(1.0f, 0, 0, 0)));
	EXPECT_EQ(DrawableID(256), DrawableID(ColorRGBA<float>(0, 1.0f/256.0f, 0, 0)));
	EXPECT_EQ(DrawableID(256*256), DrawableID(ColorRGBA<float>(0, 0, 1.0f / 256.0f, 0)));
	EXPECT_EQ(DrawableID(256*256*256), DrawableID(ColorRGBA<float>(0, 0, 0, 1.0f / 256.0f)));

}

TEST(DrawableIDTest, TestFromColorUC)
{
	EXPECT_EQ(DrawableID(0), DrawableID(ColorRGBA<unsigned char>(0, 0, 0, 0)));
	EXPECT_EQ(DrawableID(30), DrawableID(ColorRGBA<unsigned char>(30, 0, 0, 0)));
	EXPECT_EQ(DrawableID(255), DrawableID(ColorRGBA<unsigned char>(255, 0, 0, 0)));
	EXPECT_EQ(DrawableID(256), DrawableID(ColorRGBA<unsigned char>(0, 1, 0, 0)));
	EXPECT_EQ(DrawableID(256*256), DrawableID(ColorRGBA<unsigned char>(0, 0, 1, 0)));
	EXPECT_EQ(DrawableID(256*256*256), DrawableID(ColorRGBA<unsigned char>(0, 0, 0, 1)));
	EXPECT_EQ(DrawableID(256*256*256+1), DrawableID(ColorRGBA<unsigned char>(1, 0, 0, 1)));
}


TEST(DrawableIDTest, TestToColor)
{
	EXPECT_EQ(ColorRGBA<float>(0.0f, 0.0f, 0.0f, 0.0f), DrawableID(0).toColor());
	EXPECT_EQ(ColorRGBA<float>(30.0f / 256.0f, 0.0f, 0.0f, 0.0f), DrawableID(30).toColor());
	EXPECT_EQ(ColorRGBA<float>(0.0f, 1.0f / 256.0f, 0.0f, 0.0f), DrawableID(256).toColor());
	EXPECT_EQ(ColorRGBA<float>(0.0f, 0.0f, 1.0f / 256.0f, 0.0f), DrawableID(256 * 256).toColor());
	//EXPECT_EQ(ColorRGBA<float>(0.0f, 0.0f, 0.0f, 1.0f / 256.0f), DrawableID(256 * 256 * 256).toColor());

}
