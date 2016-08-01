#include "Quad3d.h"
#include "Point3d.h"
#include "PolyLine3d.h"

using namespace Crystal::Math;

template<typename T>
Quad3d<T>::Quad3d() :
	origin(Vector3d<T>(0,0,0)),
	uVector(Vector3d<T>(1,0,0)),
	vVector(Vector3d<T>(0,1,0))
{
}

template<typename T>
Quad3d<T>::Quad3d<T>(const Vector3d<T>& origin, const Vector3d<T>& uVector, const Vector3d<T>& vVector) :
	origin(origin),
	uVector(uVector),
	vVector(vVector)
{}

template<typename T>
Quad3d<T> Quad3d<T>::fromPositions(const Vector3d<T>& origin, const Vector3d<T>& pos1, const Vector3d<T>& pos2)
{
	return Quad3d<T>(origin, pos1 - origin, pos2 - origin);
}

template<typename T>
Quad3d<T> Quad3d<T>::XYPlane(const Vector3d<T>& origin)
{
	return Quad3d<T>(origin, Vector3d<T>(1, 0, 0), Vector3d<T>(0, 1, 0));
}

template<typename T>
Quad3d<T> Quad3d<T>::YZPlane(const Vector3d<T>& origin)
{
	return Quad3d<T>(origin, Vector3d<T>(0, 1, 0), Vector3d<T>(0, 0, 1));
}

template<typename T>
Quad3d<T> Quad3d<T>::ZXPlane(const Vector3d<T>& origin)
{
	return Quad3d<T>(origin, Vector3d<T>(0, 0, 1), Vector3d<T>(1, 0, 0));
}

template<typename T>
Vector3d<T> Quad3d<T>::getNormal() const
{
	const auto v1 = uVector.normalized();
	const auto v2 = vVector.normalized();
	return v1.getOuterProduct(v2).normalized();
}

template<typename T>
Vector3d<T> Quad3d<T>::getPosition(const T u, const T v) const
{
	return origin + (uVector * u) + (vVector * v);	
}

template<typename T>
Point3d<T> Quad3d<T>::getPoint(const T u, const T v) const
{
	const auto& pos = getPosition(u, v);
	const auto& norm = getNormal();
	const Vector2d<T> param(u, v);
	return Point3d<T>(pos, norm, param);
}

template<typename T>
std::array<Vector3d<T>, 4> Quad3d<T>::getPositions() const
{
	const auto v1 = getPosition(0, 0);
	const auto v2 = getPosition(1, 0);
	const auto v3 = getPosition(1, 1);
	const auto v4 = getPosition(0, 1);
	return{ v1,v2,v3,v4 };
}

template<typename T>
bool Quad3d<T>::equals(const Quad3d<T>& rhs) const
{
	return
		origin == rhs.origin &&
		uVector == rhs.uVector &&
		vVector == rhs.vVector;
}

template<typename T>
bool Quad3d<T>::operator==(const Quad3d<T>& rhs) const
{
	return equals(rhs);
}

template<typename T>
bool Quad3d<T>::operator!=(const Quad3d<T>& rhs) const
{
	return !equals(rhs);
}

#include "Curve3d.h"

template<typename T>
Curve3d<T> Quad3d<T>::toCurve3d() const
{
	Curve3d<T> curve(2, 2);
	curve.set(0, 0, getPoint(0, 0));
	curve.set(0, 1, getPoint(0, 1));
	curve.set(1, 0, getPoint(1, 0));
	curve.set(1, 1, getPoint(1, 1));
	return curve;
}

template<typename T>
Polyline3d<T> Quad3d<T>::toPolyline() const
{
	Polyline3d<T> result;
	const auto& positions = getPositions();
	for (int i = 0; i < positions.size(); ++i) {
		result.add(positions[i]);
	}
	return result;
}

template<typename T>
T Quad3d<T>::getArea() const
{
	return uVector.getOuterProduct(vVector).getLength();
}


template class Quad3d<float>;
template class Quad3d<double>;