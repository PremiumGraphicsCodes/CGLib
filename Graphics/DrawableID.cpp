#include "DrawableID.h"

#include "ColorRGBA.h"

using namespace Crystal::Graphics;

ColorRGBA<float> DrawableID::toColor() const
{
	const float red = 0.0f;
	const float green = id % 255;
	const float blue = (id / 255) % 255;
	const float alpha = 255;
	return ColorRGBA<float>(red, green, blue, alpha);
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