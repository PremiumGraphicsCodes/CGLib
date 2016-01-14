#include "ColorRGB.h"

using namespace Crystal::Graphics;

template<typename T>
ColorRGB<T>::ColorRGB() :
	red(0),
	green(0),
	blue(0)
{}

template<typename T>
ColorRGB<T>::ColorRGB(const T red, const T green, const T blue) :
	red(red), green(green), blue(blue)
{}

template<typename T>
bool ColorRGB<T>::equals(const ColorRGB& rhs) const
{
	return
		(red == rhs.getRed()) &&
		(green == rhs.getGreen()) &&
		(blue == rhs.getBlue());
}

template<typename T>
void ColorRGB<T>::add(const ColorRGB& rhs)
{
	red += rhs.red;
	green += rhs.green;
	blue += rhs.blue;
}


template<typename T>
std::vector<T> ColorRGB<T>::toArray3() const
{
	std::vector<T> results(3);
	results[0] = red;
	results[1] = green;
	results[2] = blue;
	return results;
}

template<typename T>
ColorRGB<T> ColorRGB<T>::getAdd(const ColorRGB& rhs) const
{
	return ColorRGB<T>(red + rhs.red, green + rhs.green, blue + rhs.blue);
}


template<typename T>
ColorRGB<T> ColorRGB<T>::scale(const T scale)
{
	red *= scale;
	green *= scale;
	blue *= scale;
	return *this;
}


template<typename T>
bool ColorRGB<T>::isValid() const
{
	return
		(0 <= red && red <= 255) &&
		(0 <= green && green <= 255) &&
		(0 <= blue && blue <= 255);
}


template class ColorRGB<unsigned char>;
template class ColorRGB<float>;
template class ColorRGB<double>;
