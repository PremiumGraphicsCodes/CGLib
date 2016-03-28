#include "ColorMap.h"

using namespace Crystal::Graphics;

ColorMap::ColorMap() :
	min_(0.0f),
	max_(1.0f)
{}

ColorMap::ColorMap(const float min, const float max, const int resolution) :
	min_(min),
	max_(max),
	reds(resolution),
	greens(resolution),
	blues(resolution),
	alphas(resolution)
{
	assert(isValid());
}

ColorMap::ColorMap(const std::vector<ColorRGBA<float> >& colors) :
	min_(0.0f),
	max_(1.0f)
{
	setColors(colors);
}

void ColorMap::setColors(const std::vector<ColorRGBA<float> >& colors)
{
	reds.clear();
	greens.clear();
	blues.clear();
	alphas.clear();
	for (const ColorRGBA<float>& c : colors) {
		reds.push_back(c.getRed());
		greens.push_back(c.getGreen());
		blues.push_back(c.getBlue());
		alphas.push_back(c.getAlpha());
	}
}

void ColorMap::setColor(const size_t i, const ColorRGBA<float>& c)
{
	reds[i] = c.getRed();
	greens[i] = c.getGreen();
	blues[i] = c.getBlue();
	alphas[i] = c.getAlpha();
}

ColorRGBA<float> ColorMap::getInterpolatedColor(const float v) const
{
	if (v <= min_) {
		return Graphics::ColorRGBA<float>(reds.front(), greens.front(), blues.front(), alphas.front());// getColor( min_ );
	}
	if (v >= max_) {
		return Graphics::ColorRGBA<float>(reds.back(), greens.back(), blues.back(), alphas.back());
	}
	const int index1 = getIndex(v);
	const int index2 = getIndex(v) + 1;

	if (index1 < 0) {
		return Graphics::ColorRGBA<float>(reds.front(), greens.front(), blues.front(), alphas.front());// getColor( min_ );
	}
	if (index2 >= getResolution()) {
		return Graphics::ColorRGBA<float>(reds.back(), greens.back(), blues.back(), alphas.back());
	}
	const float v1 = getValueFromIndex(index1);
	const float v2 = getValueFromIndex(index2);

	Range range(v1, v2);
	const float ratio = range.getNormalized(v);

	auto c1 = getColorFromIndex(index1).getScaled(ratio);
	auto c2 = getColorFromIndex(index2).getScaled(1.0f - ratio);
	return c1 + c2;
}
