#include "PolyLine3d.h"
#include "Line3d.h"

using namespace Crystal::Math;

template<typename T>
Polyline3d<T>::Polyline3d()
{
}

template<typename T>
Polyline3d<T>::Polyline3d(const std::vector<Vector3d<T>>& positions) :
	positions(positions)
{}

template<typename T>
std::vector<Line3d<T>> Polyline3d<T>::toLines() const
{
	std::vector<Line3d<T>> lines;
	for (int i = 0; i < positions.size() - 1; ++i) {
		Line3d<T> l(positions[i], positions[i + 1]);
		lines.push_back(l);
	}
	lines.push_back(Line3d<T>(positions.back(), positions.front()));

	return lines;
}

template<typename T>
std::vector<Vector3d<T>> Polyline3d<T>::getPositions() const
{
	return positions;
}

template<typename T>
bool Polyline3d<T>::equals(const Polyline3d<T>& rhs) const
{
	return positions == rhs.positions;
}

template<typename T>
bool Polyline3d<T>::operator==(const Polyline3d<T>& rhs) const
{
	return equals(rhs);
}

template<typename T>
bool Polyline3d<T>::operator!=(const Polyline3d<T>& rhs) const
{
	return !equals(rhs);
}


template class Polyline3d<float>;
template class Polyline3d<double>;