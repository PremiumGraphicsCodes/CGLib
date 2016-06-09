#include "Cylinder.h"
#include "Circle3d.h"
#include "Tolerance.h"

using namespace Crystal::Math;

template<typename T>
Cylinder<T>::Cylinder() :
	radius(0.5),
	height(1)
{
}

template<typename T>
Cylinder<T>::Cylinder(const Vector3d<T>& center, const T radius, const T height) :
	center(center),
	radius(radius),
	height(height)
{
}

template<typename T>
T Cylinder<T>::getVolume() const
{
	return radius * radius * Tolerance<T>::getPI() * height;
}

template<typename T>
Vector3d<T> Cylinder<T>::getPosition(const Param<T> u, const Param<T> v) const
{
	return getPosition(u.toAngle(), v);
}

template<typename T>
Vector3d<T> Cylinder<T>::getPosition(const Angle<T> u, const Param<T> v) const
{
	const auto x = radius * u.getCos();
	const auto y = radius * v.get() * height;
	const auto z = radius * u.getSin();

	return Vector3d<T>(x, y, z) + Vector3d<T>(0, -height*0.5, 0) + center;
}

template<typename T>
Point3d<T> Cylinder<T>::getPoint(const Param<T> u, const Param<T> v) const
{
	const auto position = getPosition(u, v);
	//const auto normal = position.getX() - center;
	const Vector3d<T> normal;
	const Vector2d<T> param;
	return Point3d<T>(position, normal, param);
}


template<typename T>
Circle3d<T> Cylinder<T>::getBotton() const
{
	return Circle3d<T>(radius, center - Vector3d<T>(0, height*T{ 0.5 }, 0), Vector3d<T>(0, -1, 0));
}

template<typename T>
Circle3d<T> Cylinder<T>::getTop() const
{
	return Circle3d<T>(radius, center + Vector3d<T>(0, height*T{ 0.5 }, 0), Vector3d<T>(0, 1, 0));
	//return Circle3d<T>
}

#include "Circle2d.h"
#include "Curve3d.h"

template<typename T>
std::vector< Curve3d<T> > Cylinder<T>::toCurve3ds(int number) const
{
	Circle2d<T> bottom(radius);
	Curve2d<T> curve2d = bottom.toCurve2d(number);

	Curve3d<T> topCurve(curve2d);
	topCurve.transform(Matrix3d<T>::RotateX(Tolerance<T>::getPI()*T { 0.5 }));
	topCurve.move(Vector3d<T>(0.0, height*T{ 0.5 }, 0.0));

	Curve3d<T> bottomCurve(curve2d);
	bottomCurve.transform(Matrix3d<T>::RotateX(-Tolerance<T>::getPI()*T { 0.5 }));
	bottomCurve.move(Vector3d<T>(0.0, -height*T{ 0.5 }, 0.0));

	Curve3d<T> sideCurve(2, number);
	for (int i = 0; i < number; ++i) {
		const auto param = Param<T>(i / (T)number);
		const auto& v1 = getPoint(param, Param<T>(0));
		const auto& v2 = getPoint(param, Param<T>(1));
		sideCurve.set(0, i, v1);
		sideCurve.set(1, i, v2);
	}

	std::vector<Curve3d<T>> curves;
	curves.push_back(topCurve);
	curves.push_back(sideCurve);
	curves.push_back(bottomCurve);
	return curves;
}


/*
template<typename T>
T Cylinder<T>::getRadius() const
{

}
*/

template class Cylinder<float>;
template class Cylinder<double>;