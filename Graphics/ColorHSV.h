#ifndef __CRYSTAL_GRAPHICS_COLOR_HSV_H__
#define __CRYSTAL_GRAPHICS_COLOR_HSV_H__

#include "ColorRGB.h"
#include <cassert>

namespace Crystal {
	namespace Graphics {

template<typename T>
class ColorHSV {
public:

	ColorHSV() :
		h( 0.0 ),
		s( 0.0 ),
		v( 0.0 )
	{}

	ColorHSV( const T h, const T s, const T v ) :
		h( h ),
		s( s ),
		v( v )
	{}


	/*
	ColorHSV( const ColorRGB<float>& rgb ) {
	}
	*/


	T getH() const { return h; }

	T getS() const { return s; }

	T getV() const { return v; }

	void setH( const T h ) { this->h = h; }

	void setS( const T s ) { this->s = s; }

	void setV( const T v ) { this->v = v; }

	bool operator==( const ColorHSV& rhs ) const {
		return
			h == rhs.getH() &&
			s == rhs.getS() &&
			v == rhs.getV();
	}
	
private:
	T h;
	T s;
	T v;
};
	}
}

#endif