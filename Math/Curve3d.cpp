#include "Curve3d.h"

using namespace Crystal::Math;

template<typename T>
Curve3d<T>::Curve3d()
{}

template<typename T>
Curve3d<T>::Curve3d(const int u, const int v) :
	uNumber(u),
	vNumber(v)
{
	for (int i = 0; i < v; ++i) {
		std::vector<Point3d<T>> v(u);
		points.push_back(v);
	}
}

template<typename T>
Point3d<T> Curve3d<T>::get(const int u, const int v) const
{
	return points[u][v];
}

template<typename T>
void Curve3d<T>::set(const int u, const int v, const Point3d<T>& pos)
{
	points[u][v] = pos;
}

template class Curve3d<float>;
template class Curve3d<double>;