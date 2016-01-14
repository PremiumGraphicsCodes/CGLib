#ifndef __CRYSTAL_GRAPHICS_IMAGE_RGBA_H__
#define __CRYSTAL_GRAPHICS_IMAGE_RGBA_H__

#include <vector>
#include <cassert>

#include <memory>

#include "ColorRGBA.h"
#include "ColorConverter.h"

namespace Crystal {
	namespace Graphics {

enum class ImageFileFormat
{
	BMP,
	PNG,
	JPG,
};


template< typename T >
class ImageRGBA {
public:
	ImageRGBA() :
		width( 0 ),
		height( 0 )
	{}

	ImageRGBA( const int width, const int height ) :
		width( width ),
		height( height ),
		values( width * height * 4 )
	{}

	ImageRGBA( const int width, const int height, const std::vector< T >& values ) :
		width( width ),
		height( height ),
		values( values )
	{
		assert( isValid() );
	}

	ImageRGBA(const int width, const int height, const T v) :
		width(width),
		height(height)
	{
		values.resize(width * height * 4);
		std::fill(values.begin(), values.end(), v);
		assert(isValid());
	}

	explicit ImageRGBA(const std::string& filename) { read(filename); }

	static ImageRGBA White(const int width, const int height) {
		std::vector<T> values(width * height * 4);
		for (int i = 0; i < width * height; ++i) {
			values[i * 4] = 255;
			values[i * 4 + 1] = 255;
			values[i * 4 + 2] = 255;
			values[i * 4 + 3] = 255;

		}
		return ImageRGBA<T>(width, height, values);
	}

	static ImageRGBA Black(const int width, const int height) {
		std::vector<T> values(width * height * 4);
		for (int i = 0; i < width * height; ++i) {
			values[i * 4] = 0;
			values[i * 4 + 1] = 0;
			values[i * 4 + 2] = 0;
			values[i * 4 + 3] = 255;
		}
		return ImageRGBA<T>(width, height, values);
	}



	static ImageRGBA Red(const int width, const int height) {
		std::vector<T> values(width * height * 4);
		for (int i = 0; i < width * height; ++i) {
			values[i * 4] = 255;
			values[i * 4 + 3] = 255;
		}
		return ImageRGBA<T>(width, height, values);
	}

	static ImageRGBA Green(const int width, const int height) {
		std::vector<T> values(width * height * 4);
		for (int i = 0; i < width * height; ++i) {
			values[i * 4 + 1] = 255;
			values[i * 4 + 3] = 255;
		}
		return ImageRGBA<T>(width, height, values);
	}

	static ImageRGBA Blue(const int width, const int height) {
		std::vector<T> values(width * height * 4);
		for (int i = 0; i < width * height; ++i) {
			values[i * 4 + 2] = 255;
			values[i * 4 + 3] = 255;
		}
		return ImageRGBA<T>(width, height, values);
	}



	int getWidth() const { return width; }

	int getHeight() const { return height; }

	//std::vector< T > getValues() const { return values; }

	bool isValid() const { return ((width * height * 4) == values.size()); }

	void setColor(const int i, const int j, const ColorRGBA<T>& c) {
		const auto index = getIndex1d(i, j);
		values[index] = c.getRed();
		values[index+1] = c.getGreen();
		values[index+2] = c.getBlue();
		values[index+3] = c.getAlpha();
	}

	int getIndex1d(const int x, const int y) const { return (y * width + x) * 4; }

	ColorRGBA<T> getColor(const int x, const int y) const {
		const auto index = getIndex1d(x, y);
		const auto r = values[index];
		const auto g = values[index+1];
		const auto b = values[index+2];
		const auto a = values[index+3];
		return ColorRGBA<T>(r, g, b, a);
	}

	void changeSize(const int sizeX, const int sizeY);

	std::vector<T> getValues() const { return values; }

	bool equals(const ImageRGBA<T>& rhs) const {
		return
			(width == rhs.width) &&
			(height == rhs.height) &&
			(values == rhs.values);
	}

	bool operator==(const ImageRGBA<T>& rhs) const { return equals(rhs); }

	bool operator!=(const ImageRGBA<T>& rhs) const { return !equals(rhs); }


	void read(const std::string& filename);

	void save(const std::string& filename, const ImageFileFormat format) const;

private:
	int width;
	int height;
	std::vector< T > values;
};

	}
}

#endif