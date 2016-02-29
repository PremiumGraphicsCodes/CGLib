#include "Line3d.h"

using namespace Crystal::Math;

template<typename T>
Line3d<T>::Line3d() :
	start(Vector3d<T>(0, 0, 0)),
	vector(Vector3d<T>(0, 0, 0))
{}

template<typename T>
Line3d<T>::Line3d(const Vector3d<T>& start, const Vector3d<T>& end) :
	start(start),
	vector(end - start)
{
}

template<typename T>
void Line3d<T>::moveStartTo(const Vector3d<T>& p)
{
	this->vector += (getStart() - p);
	this->start = p;
}

template<typename T>
bool Line3d<T>::equals(const Line3d<T>& rhs) const
{
	return
		this->start == rhs.start &&
		this->vector == rhs.vector;
}

template<typename T>
T Line3d<T>::getDistance(const Vector3d<T>& position) const
{
	const auto v = position - this->start;
	const auto area = this->vector.getOuterProduct(v).getLength();
	return area / this->getLength();
}


template<typename T>
Vector3dVector<T> Line3d<T>::toPositionsByLength(const double divideLength) const
{
	Vector3dVector<T> positions;
	const unsigned int howMany = static_cast<unsigned int>(static_cast<double>(getLength()) / divideLength);
	return toPositionsByNumber(howMany);
}


template<typename T>
Vector3dVector<T> Line3d<T>::toPositionsByNumber(const unsigned int howMany) const
{
	Vector3dVector<T> positions;
	const auto dt = T(1) / static_cast<T>(howMany);
	for (size_t i = 0; i < howMany; ++i) {
		const auto param = dt * i;
		positions.emplace_back(getPosition(param));
	}
	return std::move(positions);
}



template class Line3d<float>;
template class Line3d<double>;