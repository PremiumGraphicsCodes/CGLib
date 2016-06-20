#include "DrawableID.h"

#include "ColorRGBA.h"

using namespace Crystal::Graphics;

/*
DrawableID::DrawableID(const unsigned char r, const unsigned char g, const unsigned char b, const unsigned char a)
{
	id = r % 256;
	id += (g * 255) % 256;
	//id += b * 255 * 255;
}
*/

DrawableID::DrawableID(const ColorRGBA<float>& c)
{
	fromColor(c);
}

DrawableID::DrawableID(const ColorRGBA<unsigned char>& c)
{
	ColorRGBA<float> cf(c.getRed() / 256.0f, c.getGreen() / 256.0f, c.getBlue() / 256.0f, c.getAlpha() / 256.0f);
	fromColor(cf);
}

void DrawableID::fromColor(const ColorRGBA<float>& c)
{
	id = c.getRed() * 256;
	id += c.getGreen() * 256 * 256;
	id += c.getBlue() * 256 * 256 * 256;

}


ColorRGBA<float> DrawableID::toColor() const
{
	const float red = (id % 256) / 256.0f;
	const float green = ((id / 256) % 256) / 256.0f;
	const float blue = ((id / 256 / 256) % (256 * 256)) / 256.0f;
	const float alpha = 1.0f;
	return ColorRGBA<float>(red, green, blue, alpha);
}
