#include "DrawableID.h"

#include "ColorRGBA.h"

using namespace Crystal::Graphics;

ColorRGBA<float> DrawableID::toColor() const
{
	const float red = (id % 256) / 256.0f;
	const float green = ((id / 256) % 256) / 256.0f;
	const float blue = ((id / 256 / 256) % (256 * 256)) / 256.0f;
	const float alpha = 1.0f;
	return ColorRGBA<float>(red, green, blue, alpha);
}
