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

ColorRGBA<float> DrawableID::toColor() const
{
	const float red = (id % 256) / 256.0f;
	const float green = ((id / 256) % 256) / 256.0f;
	const float blue = ((id / 256 / 256) % (256 * 256)) / 256.0f;
	const float alpha = 1.0f;
	return ColorRGBA<float>(red, green, blue, alpha);
}
