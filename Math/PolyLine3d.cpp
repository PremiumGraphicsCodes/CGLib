#include "PolyLine3d.h"
#include "Line3d.h"

using namespace Crystal::Math;

template<typename T>
PolyLine3d<T>::PolyLine3d()
{
}

template<typename T>
PolyLine3d<T>::PolyLine3d(const std::vector<Vector3d<T>>& positions) :
	positions(positions)
{}

template<typename T>
std::vector<Line3d<T>> PolyLine3d<T>::toLines() const
{
	std::vector<Line3d<T>> lines;
	for (int i = 0; i < positions.size() - 1; ++i) {
		Line3d<T> l(positions[i], positions[i + 1]);
		lines.push_back(l);
	}
	return lines;
}

template<typename T>
std::vector<Vector3d<T>> PolyLine3d<T>::getPositions() const
{
	return positions;
}


template class PolyLine3d<float>;
template class PolyLine3d<double>;