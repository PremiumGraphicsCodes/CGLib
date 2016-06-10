#include "CircularCurve3d.h"

using namespace Crystal::Math;

template<typename T>
CircularCurve3d<T>::CircularCurve3d()
{
}

template<typename T>
CircularCurve3d<T>::CircularCurve3d(const Point2d<T>& center, const Curve2d<T>& curve2d) :
	center(center)
{
	for (int i = 0; i < curve2d.size(); ++i) {
		Point3d<T> p(curve2d[i]);
		points.push_back(p);
	}
}


template<typename T>
CircularCurve3d<T>::CircularCurve3d(const Point3d<T>& center, const std::vector<Point3d<T>>& points) :
	center(center),
	points(points)
{}

template<typename T>
Point3d<T> CircularCurve3d<T>::get(const int u) const
{
	return points[u];
}

template<typename T>
void CircularCurve3d<T>::move(const Vector3d<T>& v)
{
	for (auto& p : points) {
		p.move(v);
	}
	center.move(v);
}

template<typename T>
void CircularCurve3d<T>::transform(const Matrix3d<T>& matrix)
{
	for (auto& p : points) {
		p.transform(matrix);
	}
	center.transform(matrix);
}

template class CircularCurve3d<float>;
template class CircularCurve3d<double>;