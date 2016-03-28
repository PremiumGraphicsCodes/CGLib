#ifndef __CRYSTAL_GRAPHICS_COLOR_HSV_H__
#define __CRYSTAL_GRAPHICS_COLOR_HSV_H__

#include "ColorRGBA.h"
#include <cassert>

namespace Crystal {
	namespace Graphics {
		template<typename>
		class ColorRGBA;

class ColorHSV
{
public:

	ColorHSV();

	ColorHSV(const float h, const float s, const float v);

	float getH() const { return h; }

	float getS() const { return s; }

	float getV() const { return v; }

	void setH( const float h ) { this->h = h; }

	void setS( const float s ) { this->s = s; }

	void setV( const float v ) { this->v = v; }

	bool equals(const ColorHSV& rhs) const;

	bool operator==( const ColorHSV& rhs ) const {
		return equals(rhs);
	}

	bool operator!=(const ColorHSV& rhs) const {
		return !equals(rhs);
	}

	ColorRGBA<float> toColorRGBA() const;
	
private:
	float h;
	float s;
	float v;
};
	}
}

#endif