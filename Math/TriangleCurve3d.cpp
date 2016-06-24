#include "TriangleCurve3d.h"

using namespace Crystal::Math;

template<typename T>
TriangleCurve3d<T>::TriangleCurve3d(const int num)
{
	for (int i = 0; i < num; ++i) {
		std::vector<Point3d<T>> point(i+1);
		points.push_back(point);
	}
}

template<typename T>
Point3d<T> TriangleCurve3d<T>::get(const int u, const int v) const
{
	return points[u][v];
}

template<typename T>
void TriangleCurve3d<T>::set(const int u, const int v, const Point3d<T>& p)
{
	points[u][v] = p;
}

/*
template<typename T>
TriangleCell<T> TriangleCurve3d<T>::toCells() const
{
	std::vector< TriangleCell > cells;
	for (int i = 1; i < getSize(); ++i) {
		//get(i,0)
		for (int j = i - 1; j <= i; ++j) {
			auto v0 = get(i - 1, j);
			auto v1 = get(i, j);
			auto v2 = get(i, j + 1);
			TriangleCell<T> cell(v0, v1, v2);
			cells.push_back(cell);
		}
	}
	return cells;
}
*/

template class TriangleCurve3d<float>;
template class TriangleCurve3d<double>;