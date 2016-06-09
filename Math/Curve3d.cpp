#include "Curve3d.h"

using namespace Crystal::Math;

template<typename T>
Curve3d<T>::Curve3d()
{}

template<typename T>
Curve3d<T>::Curve3d(const Curve2d<T>& curve2d) :
	uNumber(1),
	vNumber(static_cast<int>(curve2d.size()))
{
	std::vector<Point3d<T>> ps;
	for (int i = 0; i < curve2d.size(); ++i) {
		Point3d<T> p(curve2d[i]);
		ps.push_back(p);
	}
	points.push_back(ps);
}


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

template<typename T>
void Curve3d<T>::move(const Vector3d<T>& v)
{
	for (int i = 0; i < uNumber; ++i) {
		for (int j = 0; j < vNumber; ++j) {
			points[i][j].move(v);
		}
	}
}

template<typename T>
void Curve3d<T>::transform(const Matrix3d<T>& matrix)
{
	for (int i = 0; i < uNumber; ++i) {
		for (int j = 0; j < vNumber; ++j) {
			points[i][j].transform(matrix);
		}
	}
}


template class Curve3d<float>;
template class Curve3d<double>;