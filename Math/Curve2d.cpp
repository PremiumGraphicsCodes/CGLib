#include "Curve2d.h"

using namespace Crystal::Math;

template<typename T>
Curve2d<T>::Curve2d(const std::vector<Point2d<T>>& points) :
	points(points)
{
}
