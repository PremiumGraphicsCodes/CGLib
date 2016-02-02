#include "ColorRGBA.h"

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
std::vector<T> ColorRGBA<T>::toArray3() const
{
	std::vector<T> results(3);
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

template class ColorRGBA<unsigned char>;
template class ColorRGBA<float>;
template class ColorRGBA<double>;