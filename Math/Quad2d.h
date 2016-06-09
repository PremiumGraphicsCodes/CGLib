#ifndef __CRYSTAL_MATH_QUAD_2D_H__
#define __CRYSTAL_MATH_QUAD_2D_H__

#include "Vector2d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Quad2d
{
public:
	Quad2d(const Vector2d<T>& origin, const Vector2d<T>& length);

private:
	Vector2d<T> origin;
	Vector2d<T> length;
};
	}
}

#endif