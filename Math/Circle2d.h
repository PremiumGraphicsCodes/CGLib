#ifndef __CRYSTAL_MATH_CIRCLE_2D_H__
#define __CRYSTAL_MATH_CIRCLE_2D_H__

#include "../Math/Vector2d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Circle2d
{
public:
	Circle2d();

	explicit Circle2d(const T radius);

	T getArea() const;

	std::vector<Vector2d<T>> toPoints(const int number) const;

private:
	T radius;
};
	}
}

#endif