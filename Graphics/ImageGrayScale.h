#ifndef __CRYSTAL_GRAPHICS_IMAGE_GRAY_SCALE_H__
#define __CRYSTAL_GRAPHICS_IMAGE_GRAY_SCALE_H__

#include <vector>

namespace Crystal {
	namespace Graphics {

template<typename T>
class ImageGrayScale
{
public:
	ImageGrayScale() :
		width( 0 ),
		height( 0 )
	{}

	ImageGrayScale(const int width, const int height) :
		width(width),
		height(height),
		values( width * height)
	{}

	ImageGrayScale(const int width, const int height, const std::vector<T> values) :
		width(width),
		height(height),
		values(values)
	{}

	ImageGrayScale(const int width, const int height, const T v) :
		width(width),
		height(height)
	{
		values.resize(width * height);
		std::fill(values.begin(), values.end(), v);
	}

	static ImageGrayScale<T> White(const int width, const int height) { return ImageGrayScale<T>(width, height, 0); }

	static ImageGrayScale<T> Black(const int width, const int height) { return ImageGrayScale<T>(width, height, 255); }

	bool isValid() const { return  (width * height) == values.size(); }

	int getIndex1d(const int x, const int y) const { return (x * width + y); }

	void setValue(const int x, const int y, const T v) { values[getIndex1d(x, y)] = v; }

	int getWidth() const { return width; }

	int getHeight() const { return height; }

	T getValue(const int x, const int y) const { return values[getIndex1d(x, y)]; }

	std::vector<T> getValues() const { return values; }

private:
	int width;
	int height;
	std::vector<T> values;
};
	}
}

#endif
