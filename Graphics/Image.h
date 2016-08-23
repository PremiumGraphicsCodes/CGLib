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

class IImage
{
public:
	IImage() :
		width(0),
		height(0)
	{}

	IImage(const int width, const int height) :
		width(width),
		height(height)
	{}

	virtual void read(const std::string& filename) = 0;

	virtual void save(const std::string& filename, const ImageFileFormat format) const = 0;

	int getWidth() const { return width; }

	int getHeight() const { return height; }

	void changeSize(const int width, const int height) {
		this->width = width;
		this->height = height;
	}

	int getIndex1d(const int x, const int y) const { return (y * width + x) * 4; }

private:
	int width;
	int height;
};

class Image : public IImage
{
public:
	Image() : IImage()
	{}

	Image( const int width, const int height ) : IImage(width, height),
		values( width * height * 4 )
	{}

	Image( const int width, const int height, const std::vector< unsigned char >& values ) :
		IImage(width, height),
		values( values )
	{
		assert( isValid() );
	}

	Image(const int width, const int height, const unsigned char v) :
		IImage(width, height)
	{
		values.resize(width * height * 4);
		std::fill(values.begin(), values.end(), v);
		assert(isValid());
	}

	explicit Image(const std::string& filename) { read(filename); }

	static Image White(const int width, const int height) {
		std::vector<unsigned char> values(width * height * 4);
		for (int i = 0; i < width * height; ++i) {
			values[i * 4] = 255;
			values[i * 4 + 1] = 255;
			values[i * 4 + 2] = 255;
			values[i * 4 + 3] = 255;

		}
		return Image(width, height, values);
	}

	static Image Black(const int width, const int height) {
		std::vector<unsigned char> values(width * height * 4);
		for (int i = 0; i < width * height; ++i) {
			values[i * 4] = 0;
			values[i * 4 + 1] = 0;
			values[i * 4 + 2] = 0;
			values[i * 4 + 3] = 255;
		}
		return Image(width, height, values);
	}



	static Image Red(const int width, const int height) {
		std::vector<unsigned char> values(width * height * 4);
		for (int i = 0; i < width * height; ++i) {
			values[i * 4] = 255;
			values[i * 4 + 3] = 255;
		}
		return Image(width, height, values);
	}

	static Image Green(const int width, const int height) {
		std::vector<unsigned char> values(width * height * 4);
		for (int i = 0; i < width * height; ++i) {
			values[i * 4 + 1] = 255;
			values[i * 4 + 3] = 255;
		}
		return Image(width, height, values);
	}

	static Image Blue(const int width, const int height) {
		std::vector<unsigned char> values(width * height * 4);
		for (int i = 0; i < width * height; ++i) {
			values[i * 4 + 2] = 255;
			values[i * 4 + 3] = 255;
		}
		return Image(width, height, values);
	}


	//std::vector< T > getValues() const { return values; }

	bool isValid() const { return ((getWidth() * getHeight() * 4) == values.size()); }

	void setColor(const int i, const int j, const ColorRGBA<unsigned char>& c) {
		const auto index = getIndex1d(i, j);
		values[index] = c.getRed();
		values[index+1] = c.getGreen();
		values[index+2] = c.getBlue();
		values[index+3] = c.getAlpha();
	}


	ColorRGBA<unsigned char> getColor(const int x, const int y) const {
		const auto index = getIndex1d(x, y);
		const auto r = values[index];
		const auto g = values[index+1];
		const auto b = values[index+2];
		const auto a = values[index+3];
		return ColorRGBA<unsigned char>(r, g, b, a);
	}

	void changeSize(const int sizeX, const int sizeY);

	std::vector<unsigned char> getValues() const { return values; }

	bool equals(const Image& rhs) const {
		return
			(getWidth() == rhs.getWidth()) &&
			(getHeight() == rhs.getHeight()) &&
			(values == rhs.values);
	}

	bool operator==(const Image& rhs) const { return equals(rhs); }

	bool operator!=(const Image& rhs) const { return !equals(rhs); }

	void read(const std::string& filename) override;

	void save(const std::string& filename, const ImageFileFormat format) const override;

	Image reversed()
		{
			Image dest(getWidth(), getHeight());
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
	std::vector< unsigned char > values;
};

class Imagef : public IImage
{
public:
	Imagef() : IImage()
	{}

	Imagef(const int width, const int height) :
		IImage(width, height),
		values(width * height * 4)
	{}

	Imagef(const int width, const int height, const std::vector< float >& values) :
		IImage(width, height),
		values(values)
	{
		assert(isValid());
	}

	Imagef(const int width, const int height, const float v) :
		IImage(width, height)
	{
		values.resize(width * height * 4);
		std::fill(values.begin(), values.end(), v);
		assert(isValid());
	}

	explicit Imagef(const std::string& filename) { read(filename); }

	static Imagef White(const int width, const int height) {
		std::vector<float> values(width * height * 4);
		for (int i = 0; i < width * height; ++i) {
			values[i * 4] = 1.0f;
			values[i * 4 + 1] = 1.0f;
			values[i * 4 + 2] = 1.0f;
			values[i * 4 + 3] = 1.0f;

		}
		return Imagef(width, height, values);
	}

	static Imagef Black(const int width, const int height) {
		std::vector<float> values(width * height * 4);
		for (int i = 0; i < width * height; ++i) {
			values[i * 4] = 0;
			values[i * 4 + 1] = 0;
			values[i * 4 + 2] = 0;
			values[i * 4 + 3] = 1.0f;
		}
		return Imagef(width, height, values);
	}

	static Imagef Red(const int width, const int height) {
		std::vector<float> values(width * height * 4);
		for (int i = 0; i < width * height; ++i) {
			values[i * 4] = 1.0f;
			values[i * 4 + 3] = 1.0f;
		}
		return Imagef(width, height, values);
	}

	static Imagef Green(const int width, const int height) {
		std::vector<float> values(width * height * 4);
		for (int i = 0; i < width * height; ++i) {
			values[i * 4 + 1] = 1.0f;
			values[i * 4 + 3] = 1.0f;
		}
		return Imagef(width, height, values);
	}

	static Imagef Blue(const int width, const int height) {
		std::vector<float> values(width * height * 4);
		for (int i = 0; i < width * height; ++i) {
			values[i * 4 + 2] = 1.0f;
			values[i * 4 + 3] = 1.0f;
		}
		return Imagef(width, height, values);
	}

	bool isValid() const { return ((getWidth() * getHeight() * 4) == values.size()); }

	void setColor(const int i, const int j, const ColorRGBA<float>& c) {
		const auto index = getIndex1d(i, j);
		values[index] = c.getRed();
		values[index + 1] = c.getGreen();
		values[index + 2] = c.getBlue();
		values[index + 3] = c.getAlpha();
	}

	ColorRGBA<float> getColor(const int x, const int y) const {
		const auto index = getIndex1d(x, y);
		const auto r = values[index];
		const auto g = values[index + 1];
		const auto b = values[index + 2];
		const auto a = values[index + 3];
		return ColorRGBA<float>(r, g, b, a);
	}

	void changeSize(const int sizeX, const int sizeY);

	std::vector<float> getValues() const { return values; }

	bool equals(const Imagef& rhs) const {
		return
			(getWidth() == rhs.getWidth()) &&
			(getHeight() == rhs.getHeight()) &&
			(values == rhs.values);
	}

	bool operator==(const Imagef& rhs) const { return equals(rhs); }

	bool operator!=(const Imagef& rhs) const { return !equals(rhs); }


	void read(const std::string& filename);

	void save(const std::string& filename, const ImageFileFormat format) const;

	Imagef reversed()
	{
		Imagef dest(getWidth(), getHeight());
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
	std::vector< float > values;
};
	}
}

#endif