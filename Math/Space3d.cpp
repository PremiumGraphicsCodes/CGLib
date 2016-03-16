#include "Space3d.h"

using namespace Crystal::Math;

template<typename T>
Space3d<T>::Space3d(const Vector3d<T>& origin) :
	origin(origin)
{}

template<typename T>
Space3d<T>::Space3d(const Vector3d<T>& origin, const Vector3d<T>& length) :
	origin(origin),
	vector(length)
{}

template<typename T>
bool Space3d<T>::isInner(const Vector3d<float>& position) const
{
	const bool xin = (getStart().getX() <= position.getX()) && (position.getX() < getEnd().getX());
	const bool yin = (getStart().getY() <= position.getY()) && (position.getY() < getEnd().getY());
	const bool zin = (getStart().getZ() <= position.getZ()) && (position.getZ() < getEnd().getZ());
	return xin && yin && zin;
}

template<typename T>
bool Space3d<T>::isOuter(const Vector3d<float>& position) const
{
	return !isInner(position);
}

template<typename T>
std::array< Vector3d<T>, 8 > Space3d<T>::toArray() const {
	const auto x1 = getStart().getX();
	const auto y1 = getStart().getY();
	const auto z1 = getStart().getZ();
	const auto x2 = getEnd().getX();
	const auto y2 = getEnd().getY();
	const auto z2 = getEnd().getZ();

	return std::move(
		std::array< Vector3d<T>, 8 > {
		Vector3d<T>(x1, y1, z1),
			Vector3d<T>(x2, y1, z1),
			Vector3d<T>(x2, y2, z1),
			Vector3d<T>(x1, y2, z1),
			Vector3d<T>(x1, y1, z2),
			Vector3d<T>(x2, y1, z2),
			Vector3d<T>(x2, y2, z2),
			Vector3d<T>(x1, y2, z2),
	});
}

/*
template<typename T>
Space3d<T> Space3d<T>::getSubSpace(const Index3d index) const
{
	const auto originx = origin.getX() + lengthx * index[0];
	const auto originy = origin.getY() + lengthy * index[1];
	const auto originz = origin.getZ() + lengthz * index[2];
	const Vector3d<T> origin_(originx, originy, originz);

	return Space3d<T>(origin_, vector);
}
*/


template<typename T>
Space3d<T> Space3d<T>::getSubSpace(const Index3d index, const unsigned int xdiv, const unsigned int ydiv, const unsigned int zdiv) const
{
	assert(xdiv >= 1 && ydiv >= 1 && zdiv >= 1);

	const auto lengthx = vector.getX() / xdiv;
	const auto lengthy = vector.getY() / ydiv;
	const auto lengthz = vector.getZ() / zdiv;
	const Vector3d<T> length(lengthx, lengthy, lengthz);

	const auto originx = origin.getX() + lengthx * index[0];
	const auto originy = origin.getY() + lengthy * index[1];
	const auto originz = origin.getZ() + lengthz * index[2];
	const Vector3d<T> origin_(originx, originy, originz);
	return Space3d<T>(origin_, length);
}

template<typename T>
std::vector< Space3d<T> > Space3d<T>::getSubSpaces(const int xdiv, const int ydiv, const int zdiv) const
{
	assert(xdiv >= 1 && ydiv >= 1 && zdiv >= 1);

	std::vector< Space3d<T> >spaces;
	for (int i = 0; i < xdiv; ++i) {
		for (int j = 0; j < ydiv; ++j) {
			for (int k = 0; k < zdiv; ++k) {
				spaces.push_back(this->getSubSpace({ i, j, k }, xdiv, ydiv, zdiv));
			}
		}
	}
	return spaces;
}


template<typename T>
std::vector< Space3d<T> > Space3d<T>::getDividedWithEdge(const int xdiv, const int ydiv, const int zdiv) const
{
	assert(xdiv >= 1 && ydiv >= 1 && zdiv >= 1);

	std::vector< Space3d<T> >spaces;
	for (int i = -1; i <= xdiv; ++i) {
		for (int j = -1; j <= ydiv; ++j) {
			for (int k = -1; k <= zdiv; ++k) {
				spaces.push_back(this->getSubSpace({ i,j,k }, xdiv, ydiv, zdiv));
			}
		}
	}
	return spaces;

}

template<typename T>
Space3d<T> Space3d<T>::getOverlapped(const Space3d<T>& rhs) const
{
	if (!hasIntersection(rhs)) {
		return Space3d();
	}
	const auto minx = std::max<T>(this->getStart().getX(), rhs.getStart().getX());
	const auto miny = std::max<T>(this->getStart().getY(), rhs.getStart().getY());
	const auto minz = std::max<T>(this->getStart().getZ(), rhs.getStart().getZ());

	const auto maxx = std::min<T>(this->getEnd().getX(), rhs.getEnd().getX());
	const auto maxy = std::min<T>(this->getEnd().getY(), rhs.getEnd().getY());
	const auto maxz = std::min<T>(this->getEnd().getZ(), rhs.getEnd().getZ());

	const Vector3d<T> min_(minx, miny, minz);
	const Vector3d<T> max_(maxx, maxy, maxz);
	return Space3d(min_, max_ - min_);
}


template<typename T>
Space3d<T> Space3d<T>::getBoundingSpace(const Space3d<T>& rhs) const
{
	const auto minx = std::min<T>(this->getStart().getX(), rhs.getStart().getX());
	const auto miny = std::min<T>(this->getStart().getY(), rhs.getStart().getY());
	const auto minz = std::min<T>(this->getStart().getZ(), rhs.getStart().getZ());

	const auto maxx = std::max<T>(this->getEnd().getX(), rhs.getEnd().getX());
	const auto maxy = std::max<T>(this->getEnd().getY(), rhs.getEnd().getY());
	const auto maxz = std::max<T>(this->getEnd().getZ(), rhs.getEnd().getZ());
	const Vector3d<T> lengths(maxx - minx, maxy - miny, maxz - minz);
	return Space3d<T>(Vector3d<T>(minx, miny, minz), lengths);
}

template<typename T>
bool Space3d<T>::hasIntersection(const Space3d<T>& rhs) const
{
	const auto distx = std::fabs(getCenter().getX() - rhs.getCenter().getX());
	const auto lx = getLengths().getX() * 0.5 + rhs.getLengths().getX() * 0.5;

	const auto disty = std::fabs(getCenter().getY() - rhs.getCenter().getY());
	const auto ly = getLengths().getY() * 0.5 + rhs.getLengths().getY() * 0.5;

	const auto distz = std::fabs(getCenter().getZ() - rhs.getCenter().getZ());
	const auto lz = getLengths().getZ() * 0.5 + rhs.getLengths().getZ() * 0.5;

	return (distx < lx && disty < ly && distz < lz);
}

template<typename T>
T Space3d<T>::getVolume() const
{
	return vector.getX() * vector.getY() * vector.getZ();
}

template<typename T>
void Space3d<T>::move(const Vector3d<T>& v)
{
	moveStart(v);
	moveEnd(v);
}

template<typename T>
Space3d<T> Space3d<T>::moveStart(const Vector3d<T>& v) const
{
	return Space3d<T>(origin + v, vector - v);
}

template<typename T>
void Space3d<T>::moveStart(const Vector3d<T>& v)
{
	origin += v;
	vector -= v;
}

template<typename T>
void Space3d<T>::moveEnd(const Vector3d<T>& v)
{
	vector += v;
}

template<typename T>
Space3d<T> Space3d<T>::moveEnd(const Vector3d<T>& v) const
{
	return Space3d<T>(origin, vector + v);
}

template<typename T>
Space3d<T> Space3d<T>::offset(const Vector3d<T>& v) const
{
	return Space3d<T>(origin + v * 0.5, vector - v);
}

template<typename T>
bool Space3d<T>::equals(const Space3d<T>& rhs) const
{
	return
		getStart() == rhs.getStart() &&
		getLengths() == rhs.getLengths();
}


template class Space3d<float>;
template class Space3d<double>;