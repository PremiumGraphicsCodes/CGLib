#include "stdafx.h"
#include "DrawableID.h"

#include "ColorRGBA.h"

using namespace Crystal::Core;
using namespace Crystal::Graphics;


DrawableID::DrawableID(const ColorRGBA<float>& c)
{
	fromColor(c);
}

DrawableID::DrawableID(const ColorRGBA<unsigned char>& c)
{
	fromColor(c);
}

void DrawableID::fromColor(const ColorRGBA<float>& c)
{
	ColorRGBA<unsigned char> uc(c.getRed() * 255, c.getGreen() * 255, c.getBlue() * 255, c.getAlpha() * 255);
	fromColor(uc);
}

void DrawableID::fromColor(const ColorRGBA<unsigned char>& c)
{
	id = c.getAlpha();
	id <<= 8;
	id |= c.getBlue();
	id <<= 8;
	id |= c.getGreen();
	id <<= 8;
	id |= c.getRed();
}


ColorRGBA<float> DrawableID::toColor() const
{
	const int id = toUInt();
	const float red = (id % 256) / 256.0f;
	const float green = ((id / 256) % 256) / 256.0f;
	const float blue = ((id / 256 / 256) % (256 * 256)) / 256.0f;
	const float alpha = ((id / 256 / 256 / 256) % (256 * 256 * 256)) / 256.0f;;
	return ColorRGBA<float>(red, green, blue, alpha);
}
