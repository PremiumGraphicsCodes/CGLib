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
	ColorRGBA<float> cf(c.getRed() / 256.0f, c.getGreen() / 256.0f, c.getBlue() / 256.0f, c.getAlpha() / 256.0f);
	fromColor(cf);
}

void DrawableID::fromColor(const ColorRGBA<float>& c)
{
	id = c.getRed() * 256;
	id += c.getGreen() * std::pow(256,2);
	id += c.getBlue() * std::pow(256,3);
	id += c.getAlpha() * std::pow(256, 4);
}


ColorRGBA<float> DrawableID::toColor() const
{
	const float red = (id % 256) / 256.0f;
	const float green = ((id / 256) % 256) / 256.0f;
	const float blue = ((id / 256 / 256) % (256 * 256)) / 256.0f;
	const float alpha = ((id / 256 / 256 / 256) % (256 * 256 * 256)) / 256.0f;;
	return ColorRGBA<float>(red, green, blue, alpha);
}
