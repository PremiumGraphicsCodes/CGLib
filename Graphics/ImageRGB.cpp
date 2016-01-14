#include "ImageRGB.h"

using namespace Crystal::Graphics;

template<class T>
bool ImageRGB<T>::equals(const ImageRGB<T>& rhs) const
{
	if (width != rhs.width) {
		return false;
	}
	if (height != rhs.height) {
		return false;
	}
	for (size_t i = 0; i < values.size(); ++i) {
		if (values[i] != rhs.values[i]) {
			return false;
		}
	}
	return true;
}


template<class T>
std::vector<T> ImageRGB<T>::getReds() const
{
	std::vector< T > reds;
	for (ColorRGB<T> v : values) {
		reds.push_back(v.getRed());
	}
	return reds;
}

template<class T>
std::vector<T> ImageRGB<T>::getGreens() const
{
	std::vector< T > greens;
	for (ColorRGB<T> v : values) {
		greens.push_back(v.getGreen());
	}
	return greens;
}

template<class T>
std::vector<T> ImageRGB<T>::getBlues() const
{
	std::vector< T > blues;
	for (ColorRGB<T> v : values) {
		blues.push_back(v.getBlue());
	}
	return blues;
}


template class ImageRGB<unsigned char>;
template class ImageRGB<float>;
template class ImageRGB<double>;
