#include "stdafx.h"
#include "DrawableID.h"

#include "ColorRGBA.h"

using namespace Crystal::Core;
using namespace Crystal::Graphics;

DrawableID::DrawableID(const unsigned int id, const unsigned char type)
{
	this->id = id;
	this->type = type;
}


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
	type = c.getAlpha();
	id |= c.getBlue();
	id <<= 8;
	id |= c.getGreen();
	id <<= 8;
	id |= c.getRed();
}


ColorRGBA<float> DrawableID::toColor() const
{
	const int id = this->id.to_ulong();
	const float red = (id % 256) / 255.0f;
	const float green = ((id / 256) % 256) / 255.0f;
	const float blue = ((id / 256 / 256) % (265 * 256)) / 255.0f;
	const float alpha = getType() / 255.0f;
	return ColorRGBA<float>(red, green, blue, alpha);
}

unsigned char DrawableID::getType() const
{
	return type.to_ulong();
}

unsigned int DrawableID::getValue() const
{
	return id.to_ulong();
}


/*
ColorRGBA<unsigned char> DrawableID::toColorUC() const
{
	const auto r = static_cast<unsigned char>(std::bitset<32>(id & std::bitset<32>(7)).to_ulong());
	const auto g = static_cast<unsigned char>(std::bitset<32>(id & std::bitset<32>(256-1)).to_ulong());
	const auto b = std::bitset<32>(id & std::bitset<32>(256*256-1)).to_ulong();
	const auto a = std::bitset<32>(id & std::bitset<32>(256*256-1)).to_ulong();
	return ColorRGBA<unsigned char>(r, g, b, a);
}
*/