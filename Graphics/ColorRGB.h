#ifndef __CRYSTAL_GRAPHICS_COLOR_RGB_H__
#define __CRYSTAL_GRAPHICS_COLOR_RGB_H__

#include <vector>

namespace Crystal {
	namespace Graphics {

template< typename T >
class ColorRGB {
public:
	ColorRGB();

	ColorRGB(const T red, const T green, const T blue);

	void setRed( const T r ) { this->red = r; }

	void setGreen( const T g ) { this->green = g; }

	void setBlue( const T b ) { this->blue = b; }

	T getRed() const { return red; }

	T getGreen() const { return green; }

	T getBlue() const { return blue; }

	static ColorRGB White() { return ColorRGB( 255, 255, 255 ); }

	static ColorRGB Black() { return ColorRGB( 0, 0, 0 ); }

	static ColorRGB Red() { return ColorRGB( 255, 0, 0 ); }

	static ColorRGB Green() { return ColorRGB( 0, 255, 0 ); }

	static ColorRGB Blue() { return ColorRGB( 0, 0, 255 ); }

	static ColorRGB Yellow() { return ColorRGB( 255, 255, 0 ); }
	
	static ColorRGB Cyan() { return ColorRGB( 0, 255, 255 ); }

	static ColorRGB Magenta() { return ColorRGB( 255, 0, 255 ); }

	std::vector<T> toArray3() const;

	bool equals(const ColorRGB& rhs) const;

	bool operator==( const ColorRGB& rhs ) const { return equals( rhs ); }

	bool operator!=(const ColorRGB& rhs) const { return !equals( rhs ); }

	void add(const ColorRGB& rhs);

	ColorRGB<T> getAdd(const ColorRGB& rhs) const;

	ColorRGB<T> scale(const T scale);

	bool isValid() const;

private:
	T red;
	T green;
	T blue;
};

	}
}

#endif