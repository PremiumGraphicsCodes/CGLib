#ifndef __CRYSTAL_MATH_CURVE_2D_H__
#define __CRYSTAL_MATH_CURVE_2D_H__

#include "Point2d.h"
#include <vector>

namespace Crystal {
	namespace Math {

template<typename T>
class Curve2d
{
public:
	explicit Curve2d(const std::vector<Point2d<T>>& points);
private:
	std::vector<Point2d<T>> points;
};

	}
}

#endif