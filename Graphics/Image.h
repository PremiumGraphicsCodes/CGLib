#ifndef __CRYSTAL_GRAPHICS_IMAGE_RGBA_H__
#define __CRYSTAL_GRAPHICS_IMAGE_RGBA_H__

#include <vector>
#include <cassert>

#include <memory>

#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

enum class ImageFileFormat
{
	BMP,
	PNG,
	JPG,
};


template< typename T >
class Image {
public:
	Image() :
		width( 0 ),
		height( 0 )
	{}

	Image( const int width, const int height ) :
		width( width ),
		height( height ),
		values( width * height * 4 )
	{}

	Image( const int width, const int height, const std::vector< T >& values ) :
		width( width ),
		height( height ),
		values( values )
	{
		assert( isValid() );
	}

	Image(const int width, const int height, const T v) :
		width(width),
		height(height)
	{
		values.resize(width * height * 4);
		std::fill(values.begin(), values.end(), v);
		assert(isValid());
	}

	explicit Image(const std::string& filename) { read(filename); }

	static Image White(const int width, const int height) {
		std::vector<T> values(width * height * 4);
		for (int i = 0; i < width * height; ++i) {
			values[i * 4] = 255;
			values[i * 4 + 1] = 255;
			values[i * 4 + 2] = 255;
			values[i * 4 + 3] = 255;

		}
		return Image<T>(width, height, values);
	}

	static Image Black(const int width, const int height) {
		std::vector<T> values(width * height * 4);
		for (int i = 0; i < width * height; ++i) {
			values[i * 4] = 0;
			values[i * 4 + 1] = 0;
			values[i * 4 + 2] = 0;
			values[i * 4 + 3] = 255;
		}
		return Image<T>(width, height, values);
	}



	static Image Red(const int width, const int height) {
		std::vector<T> values(width * height * 4);
		for (int i = 0; i < width * height; ++i) {
			values[i * 4] = 255;
			values[i * 4 + 3] = 255;
		}
		return Image<T>(width, height, values);
	}

	static Image Green(const int width, const int height) {
		std::vector<T> values(width * height * 4);
		for (int i = 0; i < width * height; ++i) {
			values[i * 4 + 1] = 255;
			values[i * 4 + 3] = 255;
		}
		return Image<T>(width, height, values);
	}

	static Image Blue(const int width, const int height) {
		std::vector<T> values(width * height * 4);
		for (int i = 0; i < width * height; ++i) {
			values[i * 4 + 2] = 255;
			values[i * 4 + 3] = 255;
		}
		return Image<T>(width, height, values);
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

	bool equals(const Image<T>& rhs) const {
		return
			(width == rhs.width) &&
			(height == rhs.height) &&
			(values == rhs.values);
	}

	bool operator==(const Image<T>& rhs) const { return equals(rhs); }

	bool operator!=(const Image<T>& rhs) const { return !equals(rhs); }


	void read(const std::string& filename);

	void save(const std::string& filename, const ImageFileFormat format) const;


	Image<unsigned char> reversed()
		{
			Image<unsigned char> dest(getWidth(), getHeight());
			for (int x = 0; x < getWidth(); ++x) {
				for (int y = 0; y < getHeight(); ++y) {
					const auto destY = getHeight() - y - 1;
					const auto c = getColor(x, y);
					dest.setColor(x, destY, c);
				}
			}
			return dest;
		}


private:
	int width;
	int height;
	std::vector< T > values;
};

	}
}

#endif