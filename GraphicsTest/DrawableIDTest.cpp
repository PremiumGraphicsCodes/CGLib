#include "gtest\gtest.h"
#include "../Graphics/DrawableID.h"
#include "../Graphics/ColorRGBA.h"

using namespace Crystal::Graphics;

TEST(DrawableIDTest, TestToColor)
{
	DrawableID id(0);
	const auto actual = id.toColor();
	EXPECT_EQ(0.0f, actual.getRed());
	EXPECT_EQ(0.0f, actual.getGreen());
	EXPECT_EQ(0.0f, actual.getBlue());
	EXPECT_EQ(255.0f, actual.getAlpha());

}