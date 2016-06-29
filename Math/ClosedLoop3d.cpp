#include "ClosedLoop3d.h"

using namespace Crystal::Math;

template<typename T>
ClosedLoop3d<T>::ClosedLoop3d(const std::vector<Point3d<T>*>& points) :
	points(points)
{}

/*
template<typename T>
std::vector<TriangleLoop3d<T>> toTriangleLoops() const
{

}
*/

template class TriangleLoop3d<float>;
template class TriangleLoop3d<double>;
