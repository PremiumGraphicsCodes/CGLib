#ifndef __CRYSTAL_GRAPHICS_COLOR_RGBA_H__
#define __CRYSTAL_GRAPHICS_COLOR_RGBA_H__

#include <vector>

#include "ColorRGB.h"

namespace Crystal {
	namespace Graphics {

template< typename T >
class ColorRGBA {
public:
	ColorRGBA();

	ColorRGBA(const ColorRGB<T>& rgb);

	ColorRGBA(const T red, const T green, const T blue, const T alpha = 255);

	void setRed( const T r ) { rgb.setRed( r ); }

	T getRed() const { return rgb.getRed(); }

	void setGreen( const T g ) { rgb.setGreen( g ); }

	T getGreen() const { return rgb.getGreen(); }

	void setBlue(const T b) { rgb.setBlue(b); }

	T getBlue() const { return rgb.getBlue(); }

	void setAlpha(const T a) { this->alpha = a;  }

	T getAlpha() const { return alpha; }

	static ColorRGBA White() { return ColorRGBA( ColorRGB<T>::White() ); }

	static ColorRGBA Black() { return ColorRGBA( ColorRGB<T>::Black()); }

	static ColorRGBA Red() { return ColorRGBA( ColorRGB<T>::Red()); }

	static ColorRGBA Green() { return ColorRGBA( 0, 255, 0 ); }

	static ColorRGBA Blue() { return ColorRGBA( 0, 0, 255 ); }

	static ColorRGBA Yellow() { return ColorRGBA( 255, 255, 0 ); }
	
	static ColorRGBA Cyan() { return ColorRGBA( 0, 255, 255 ); }

	static ColorRGBA Magenta() { return ColorRGBA( 255, 0, 255 ); }

	std::vector<T> toArray3() const;

	std::vector<T> toArray4() const;

	bool equals(const ColorRGBA& rhs) const;

	bool operator==( const ColorRGBA& rhs ) const { return equals( rhs ); }

	bool operator!=(const ColorRGBA& rhs) const { return !equals( rhs ); }

	ColorRGBA<T> getScaled( const T f ) const { return ColorRGBA<T>( getRed() * f, getGreen() * f, getBlue() * f, alpha * f ); }

	void add( const ColorRGBA& rhs ) {
		rgb.add(rhs.rgb);
		//this->alpha+= rhs.alpha;
	}

	ColorRGBA<T> getAdded( const ColorRGBA<T>& rhs ) const {
		const ColorRGB<T> rgb = this->rgb.getAdd(rhs.rgb);
		return ColorRGBA<T>( rgb );
	}

	void operator+=( const ColorRGBA& rhs ) { add( rhs ); }

	ColorRGBA<T> operator+( const ColorRGBA& rhs ) const { return getAdded( rhs ); }

public:
	ColorRGB<T> rgb;
	T alpha;
};

template< typename T >
using ColorRGBAVector = std::vector< ColorRGBA< T > >;

static std::vector<float> toArray4( const ColorRGBAVector<float>& colors ) {
	std::vector< float > result;
	for( size_t i = 0; i < colors.size(); ++i ) {
		const std::vector<float>& color = colors[i].toArray4();
		result.insert( result.end(), color.begin(), color.end() );
	}
	return result;
}

	}
}

#endif