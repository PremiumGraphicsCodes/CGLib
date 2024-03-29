#include "Triangle3d.h"
#include "Line3d.h"
#include "TriangleCurve3d.h"
#include "Box3d.h"

using namespace Crystal::Math;

template<typename T>
Triangle3d<T>::Triangle3d() :
	v0(Vector3d<T>(0.0, 0.0, 0.0)),
	v1(Vector3d<T>(1.0, 0.0, 0.0)),
	v2(Vector3d<T>(0.0, 1.0, 0.0))
{}

template<typename T>
Triangle3d<T>::Triangle3d(const Vector3d<T>& v0, const Vector3d<T>& v1, const Vector3d<T>& v2) :
	v0(v0),
	v1(v1),
	v2(v2)
{
}

template<typename T>
Vector3d<T> Triangle3d<T>::getNormal() const
{
	const Vector3d<T> v01 = v0 - v1;
	const Vector3d<T> v02 = v1 - v2;
	return v01.getOuterProduct(v02).normalized();
}

template<typename T>
T Triangle3d<T>::getArea() const
{
	const Vector3d<T> v01 = v0 - v1;
	const Vector3d<T> v02 = v1 - v2;
	return v01.getOuterProduct(v02).getLength() * T(0.5);
}

template<typename T>
bool Triangle3d<T>::isCCW() const
{
	assert(isValid());
	return getNormal().getLength() >= 0.0f;
}

template<typename T>
bool Triangle3d<T>::isCW() const
{
	assert(isValid());
	return !isCCW();
}

template<typename T>
Vector3d<T> Triangle3d<T>::getCenter() const
{
	return (v0 + v1 + v2) / T(3);
}

template<typename T>
bool Triangle3d<T>::equals(const Triangle3d<T>& rhs) const
{
	return
		v0 == rhs.v0 &&
		v1 == rhs.v1 &&
		v2 == rhs.v2;
}

template<typename T>
bool Triangle3d<T>::operator==(const Triangle3d<T>& rhs) const
{
	return equals(rhs);
}

template<typename T>
bool Triangle3d<T>::operator!=(const Triangle3d<T>& rhs) const
{
	return !equals(rhs);
}

template<typename T>
bool Triangle3d<T>::isInside(const Vector3d<T>& position) const
{
	const auto& o1 = v0.getOuterProduct(position);
	const auto& o2 = v1.getOuterProduct(position);
	const auto& o3 = v2.getOuterProduct(position);
	const auto dir1 = o1.getInnerProduct(o1);
	const auto dir2 = o2.getInnerProduct(o2);
	return (dir1 * dir2) > T{ 0 };
}

template<typename T>
bool Triangle3d<T>::isOutside(const Vector3d<T>& position) const
{
	return !isInside(position);
}

template<typename T>
bool Triangle3d<T>::isSamePlane(const Vector3d<T>& point) const
{
	return point.isSamePlane(v0, v1, v2);
}

template<typename T>
bool Triangle3d<T>::isSamePlane(const Triangle3d<T>& rhs) const
{
	return
		isSamePlane(rhs.v0) &&
		isSamePlane(rhs.v1) &&
		isSamePlane(rhs.v2);
}

template<typename T>
bool Triangle3d<T>::isSamePlane(const Line3d<T>& line) const
{
	return
		isSamePlane(line.getStart()) &&
		isSamePlane(line.getEnd());
}

template<typename T>
std::array< Line3d<T>, 3 > Triangle3d<T>::toLines() const
{
	Line3d<T> l1(v0, v1);
	Line3d<T> l2(v1, v2);
	Line3d<T> l3(v2, v0);
	return{ l1,l2,l3 };
}

template<typename T>
TriangleCurve3d<T> Triangle3d<T>::toCurve3d() const
{
	Point3d<T> p1(v0, getNormal());
	Point3d<T> p2(v1, getNormal());
	Point3d<T> p3(v2, getNormal());
	TriangleCurve3d<T> curve(2);
	curve.set(0, 0, p1);
	curve.set(1, 0, p2);
	curve.set(1, 1, p3);
	return curve;
}

template<typename T>
Box3d<T> Triangle3d<T>::getBoundingBox() const
{
	Box3d<T> box(v0);
	box.add(v1);
	box.add(v2);
	return box;
}

template<typename T>
T Triangle3d<T>::getInscribedCircleRadius() const
{
	const auto area = getArea();
	const auto a = v1.getDistance(v0);
	const auto b = v2.getDistance(v1);
	const auto c = v0.getDistance(v2);
	return T{ 2 } * area / (a + b + c);
}


//template<typename T>
//Vector3d<T> getIntersection

/*
#include "Ray3d.h"

template<typename T>
Vector3d<T> Triangle3d<T>::getIntersection(const Line3d<T>& line) const
{
	Ray3d<T> ray(line.getStart(), line.getVector().getNormalized());
	const auto i = ray.getIntersection(*this);
	if(line.ge)
}
*/


template class Triangle3d<float>;
template class Triangle3d<double>;