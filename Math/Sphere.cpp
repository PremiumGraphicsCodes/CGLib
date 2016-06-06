#include "Sphere.h"

#include "Box3d.h"
#include "Ellipsoid.h"
#include "Curve3d.h"

using namespace Crystal::Math;

template<typename T>
Sphere<T>::Sphere() :
	center(Vector3d<T>::Zero()),
	radius(1.0f)
{}

template<typename T>
Sphere<T>::Sphere(const Vector3d<T>& center, const float radius) :
	center(center),
	radius(radius)
{}

template<typename T>
Sphere<T>::Sphere(const Box3d<T>& boundingBox)
{
	center = Vector3d<T>(boundingBox.getCenter().getX(), boundingBox.getCenter().getY(), boundingBox.getCenter().getZ());
	const Vector3d<T>& length = boundingBox.getLength();
	radius = std::min<T>(std::min<T>(length.getX(), length.getY()), length.getZ()) * T{ 0.5 };
}

template<typename T>
Sphere<T> Sphere<T>::UnitSphere()
{
	return Sphere<T>(Vector3d<T>::Zero(), 1.0f);
}


template<typename T>
Box3d<T> Sphere<T>::getBoundingBox() const {
	Math::Box3d<T> box(center, center);
	return box.getOuterOffset(radius);
}

template<typename T>
std::vector<Vector3d<T>> Sphere<T>::toPoints(const T divideLength) const
{
	std::vector<Vector3d<T>> points;

	Math::Box3d<T> box(center, center);
	box.outerOffset(radius);

	for (auto x = box.getMinX(); x <= box.getMaxX(); x += divideLength) {
		for (auto y = box.getMinY(); y <= box.getMaxY(); y += divideLength) {
			for (auto z = box.getMinZ(); z <= box.getMaxZ(); z += divideLength) {
				const Vector3d<T> pos(x, y, z);
				if (pos.getDistanceSquared(center) < radius * radius) {
					points.push_back(pos);
				}
			}
		}
	}
	return points;
}

template<typename T>
Vector3d<T> Sphere<T>::getPosition(const Angle<T> u, const Angle<T> v) const
{
	assert(0.0 <= u.getDegree().get() && u.getDegree().get() <= 360.0);
	assert(-90.0 <= v.getDegree().get() && v.getDegree().get() <= 90.0);

	const auto x = radius * u.getCos() * v.getCos();
	const auto y = radius * u.getSin() * v.getCos();
	const auto z = radius * v.getSin();
	return Vector3d<T>(x, y, z);
}

template<typename T>
Sphere<T> Sphere<T>::getInnerOffset(const float offsetLength) const
{
	Sphere sphere = *this;
	sphere.radius -= offsetLength;
	assert(sphere.isValid());
	return sphere;
}


template<typename T>
bool Sphere<T>::equals(const Sphere& rhs) const
{
	return
		Tolerance<T>::isEqualLoosely(radius, rhs.radius) &&
		(center == rhs.center);
}


template<typename T>
bool Sphere<T>::operator==(const Sphere& rhs) const
{
	return equals(rhs);
}

template<typename T>
bool Sphere<T>::operator!=(const Sphere& rhs) const
{
	return !equals(rhs);
}

template<typename T>
bool Sphere<T>::isInner(const Vector3d<T>& v) const
{
	return v.getDistanceSquared(center) < (radius * radius);
}

template<typename T>
bool Sphere<T>::isOuter(const Vector3d<T>& v) const
{
	return v.getDistanceSquared(center) > (radius * radius);
}


template<typename T>
bool Sphere<T>::isOnStrictly(const Vector3d<T>& v) const
{
	return Tolerance<T>::isEqualStrictly(v.getDistanceSquared(center), radius * radius);
}

template<typename T>
bool Sphere<T>::isOnLoosely(const Vector3d<T>& v) const
{
	return Tolerance<T>::isEqualLoosely(v.getDistanceSquared(center), radius * radius);
}


template<typename T>
Ellipsoid<T> Sphere<T>::toEllipsoid() const
{
	return Ellipsoid<T>(this->getCenter(), this->getRadius());
}

template<typename T>
Curve3d<T> Sphere<T>::toCurve3d(const int uNum, const int vNum) const
{
	Curve3d<T> curve(uNum, vNum);
	const auto du = 360.0f / static_cast<T>(uNum);
	const auto dv = 180.0f / static_cast<T>(vNum);
	for (int i = 0; i < uNum; ++i) {
		for (int j = 0; j < vNum; ++j) {
			const Degree<T> uAngle(du * i);
			const Degree<T> vAngle(dv * j - 90.0f);
			const auto& pos = getPosition(Angle<T>(uAngle), Angle<T>(vAngle));
			curve.set(i, j, pos);
		}
	}
	return curve;
}

template class Sphere<float>;
template class Sphere<double>;