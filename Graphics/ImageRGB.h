#ifndef __CRYSTAL_GRAPHICS_IMAGE_RGB_H__
#define __CRYSTAL_GRAPHICS_IMAGE_RGB_H__

#include <vector>

#include "ColorRGB.h"

#include <cassert>

namespace Crystal {
	namespace Graphics {

template< typename T >
class ImageRGB {
public:
	ImageRGB() :
		width( 0 ),
		height( 0 )
	{}

	ImageRGB( const int width, const int height ) :
		width( width ),
		height( height ),
		values( width * height )
	{}

	ImageRGB( const int width, const int height, const std::vector< ColorRGB<T> >& values ) :
		width( width ),
		height( height ),
		values( values )
	{}

	int getWidth() const { return width; }

	int getHeight() const { return height; }

	std::vector< ColorRGB<T> > getValues() const { return values; }

	ColorRGB<T> getValue(const int row, const int col) const { return values[ width * row + col ]; }

	void setValue(const int row, const int col, const ColorRGB<T>& color) { values[ width * row + col] = color; }

	bool isValid() const { return ( ( width * height ) == values.size() ); }

	bool equals(const ImageRGB& rhs) const;

	bool operator==( const ImageRGB& rhs ) const { return equals( rhs ); }

	bool operator!=( const ImageRGB& rhs ) const { return !equals( rhs ); }

	std::vector< T > getReds() const;

	std::vector< T > getGreens() const;

	std::vector< T > getBlues() const;

private:
	const int width;
	const int height;
	std::vector< ColorRGB<T> > values;
};

	}
}

#endif