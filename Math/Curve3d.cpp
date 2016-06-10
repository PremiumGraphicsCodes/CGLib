#include "Curve3d.h"

using namespace Crystal::Math;

template<typename T>
Curve3d<T>::Curve3d()
{}

template<typename T>
Curve3d<T>::Curve3d(const Curve2d<T>& curve2d) :
	points(1, static_cast<int>(curve2d.size()) )
{
	for (int i = 0; i < curve2d.size(); ++i) {
		Point3d<T> p(curve2d[i]);
		points.set(0, i, p);
	}
}


template<typename T>
Curve3d<T>::Curve3d(const int u, const int v) :
	points(u,v)
{
}

template<typename T>
Point3d<T> Curve3d<T>::get(const int u, const int v) const
{
	return points.get(u,v);
}

template<typename T>
void Curve3d<T>::set(const int u, const int v, const Point3d<T>& pos)
{
	points.set(u,v, pos);
}

template<typename T>
void Curve3d<T>::move(const Vector3d<T>& v)
{
	for (int i = 0; i < points.getSizeX(); ++i) {
		for (int j = 0; j < points.getSizeY(); ++j) {
			points.get(i,j).move(v);
		}
	}
}

template<typename T>
void Curve3d<T>::transform(const Matrix3d<T>& matrix)
{
	for (int i = 0; i < points.getSizeX(); ++i) {
		for (int j = 0; j < points.getSizeY(); ++j) {
			points.get(i,j).transform(matrix);
		}
	}
}


template class Curve3d<float>;
template class Curve3d<double>;