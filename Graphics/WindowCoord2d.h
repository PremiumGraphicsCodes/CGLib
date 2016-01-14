#ifndef __CRYSTAL_GRAPHICS_WINDOW_COORD_2D_H__
#define __CRYSTAL_GRAPHICS_WINDOW_COORD_2D_H__

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Graphics {

template <typename T>
class WindowCoord2d
{
public:
	WindowCoord2d() :
		coord(Math::Vector2d<T>(0, 0))
	{}

	explicit WindowCoord2d(const Math::Vector2d<T>& c) :
		coord(c)
	{}

	WindowCoord2d(const T x, const T y ) :
		coord(Math::Vector2d<T>(x, y))
	{}

	Math::Vector2d<T> get() const { return coord; }

	T getX() const { return coord.getX(); }

	T getY() const { return coord.getY(); }

	bool equals(const WindowCoord2d<T>& rhs) const {
		return this->coord.getX() == rhs.coord.getX() &&
			this->coord.getY() == rhs.coord.getY();
	}

	bool operator==(const WindowCoord2d<T>& rhs) const { return equals(rhs); }

	bool operator!=(const WindowCoord2d<T>& rhs) const { return !equals(rhs); }


private:
	Math::Vector2d<T> coord;

};
	}
}

#endif