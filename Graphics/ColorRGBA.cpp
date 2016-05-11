#include "ColorRGBA.h"
#include "ColorHSV.h"

#include <algorithm>

using namespace Crystal::Graphics;

template<typename T>
ColorRGBA<T>::ColorRGBA() :
	red(0),
	green(0),
	blue(0),
	alpha(0)
{}



template<typename T>
ColorRGBA<T>::ColorRGBA(const T red, const T green, const T blue, const T alpha = 255) :
	red(red),
	green(green),
	blue(blue),
	alpha(alpha)
{
}


template<typename T>
std::array<T, 3> ColorRGBA<T>::toArray3() const
{
	std::array<T, 3> results;
	results[0] = getRed();
	results[1] = getGreen();
	results[2] = getBlue();
	return results;
}

template<typename T>
std::vector<T> ColorRGBA<T>::toArray4() const
{
	std::vector<T> results(4);
	results[0] = getRed();
	results[1] = getGreen();
	results[2] = getBlue();
	results[3] = getAlpha();
	return results;
}

template<typename T>
bool ColorRGBA<T>::equals(const ColorRGBA& rhs) const
{
	return
		(getRed() == rhs.getRed()) &&
		(getGreen() == rhs.getGreen()) &&
		(getBlue() == rhs.getBlue()) &&
		(alpha == rhs.getAlpha());
}

template<typename T>
ColorHSV ColorRGBA<T>::toHSV() const
{
	const auto r = red / T{ 255 };
	const auto g = green / T{ 255 };
	const auto b = blue / T{ 255 };

	const auto min = std::min<T>(r, std::min<T>(g, b));
	const auto max = std::max<T>(r, std::max<T>(g, b));

	const auto v = max;
	const auto s = max - min;

	if (min == max) {
		const auto h = 0.0;
		return ColorHSV(h, s, v);
	}
	else if (min == b) {
		const auto h = 60.0f * (g - r) / (max - min) + 60.0f;
		return ColorHSV(h, s, v);
	}
	else if (min == r) {
		const auto h = 60.0f * (b - g) / (max - min) + 180.0f;
		return ColorHSV(h, s, v);
	}
	else if (min == g) {
		const auto h = 60.0f * (r - b) / (max - min) + 300.0f;
		return ColorHSV(h, s, v);
	}
	else {
		assert(false);
		return ColorHSV();
	}
}


template class ColorRGBA<unsigned char>;
template class ColorRGBA<float>;
template class ColorRGBA<double>;