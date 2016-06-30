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
std::vector<Vector3d<T>> Line3d<T>::toPositionsByLength(const T divideLength) const
{
	std::vector<Vector3d<T>> positions;
	const unsigned int howMany = static_cast<unsigned int>(static_cast<double>(getLength()) / divideLength);
	return toPositionsByNumber(howMany);
}


template<typename T>
std::vector<Vector3d<T>> Line3d<T>::toPositionsByNumber(const unsigned int howMany) const
{
	std::vector<Vector3d<T>> positions;
	const auto dt = T(1) / static_cast<T>(howMany);
	for (size_t i = 0; i < howMany; ++i) {
		const auto param = dt * i;
		positions.emplace_back(getPosition(param));
	}
	return std::move(positions);
}

template<typename T>
bool Line3d<T>::hasIntersection(const Line3d<T>& rhs) const
{
	const auto v1 = this->getVector().getNormalized();
	const auto v2 = rhs.getVector().getNormalized();
	const auto v3 = rhs.start - this->start;
	const auto n1 = v1.getOuterProduct(v2);
	const auto n2 = v1.getOuterProduct(v3);
	if (Tolerance<T>::isEqualLoosely(n2.getLength()), T{ 0 }) {
		return true;
	}
	if (n1.getLength() > 0) {
		if (Tolerance<T>::isEqualLoosely(n1.getOuterProduct(n2).getLength(), T{ 0 })) {
			return true;
		}
	}
	return false;
}

/*
template<typename T>
T Line3d<T>::getDistance(const Line3d<T>& rhs) const
{
	const auto l1 = this->getVector();
	const auto l2 = rhs.getVector();
	const auto v = rhs.getStart() - this->getStart();
	const auto outerProduct = l1.getOuterProduct(l2);
	const auto numerator = outerProduct.getInnerProduct( v );
	const auto denominator = outerProduct.getLength();
	return numerator / denominator;
}
*/

template<typename T>
Vector3d<T> Line3d<T>::getIntersection(const Line3d<T>& rhs) const
{
	const auto ab = this->getVector();
	const auto cd = rhs.getVector();

	const auto n1 = ab.getNormalized();
	const auto n2 = cd.getNormalized();

	const auto work1 = n1.getInnerProduct(n2);
	const auto work2 = 1 - work1 * work1;

	const auto ac = rhs.getStart() - this->getStart();

	const auto d1 = (ac.getInnerProduct(n1) - work1 * ac.getInnerProduct(n2)) / work2;
//	const auto d2 = (w1 * v3.getInnerProduct(v1) - v3.getInnerProduct(v2)) / w2;

	return getStart() + d1 * n1;
}


template class Line3d<float>;
template class Line3d<double>;