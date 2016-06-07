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
		std::vector<Vector3d<T>> v(u);
		positions.push_back(v);
	}
}

template<typename T>
Vector3d<T> Curve3d<T>::getPosition(const int u, const int v) const
{
	return positions[u][v];
}

template<typename T>
void Curve3d<T>::setPosition(const int u, const int v, const Vector3d<T>& pos)
{
	positions[u][v] = pos;
}

template class Curve3d<float>;
template class Curve3d<double>;