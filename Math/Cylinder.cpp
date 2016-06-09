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
	const auto x = u.getCos();
	const auto y = u.getSin();
	const auto z = v.get() * height;
	return Vector3d<T>(x, y, z);
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

/*
#include "Circle2d.h"

template<typename T>
std::vector< Curve3d<T> > Cylinder<T>::toCurve3ds(int number) const
{
	Circle2d<T> bottom(radius);
	const auto points = bottom.toPoints(number);
	std::vector<Vector3d<T>> tops;
	std::vector<Vector3d<T>> bottoms;
	for (int i = 0; i < points.size(); ++i) {
		tops.push_back(Vector3d<T>(points[i], height*0.5));
		bottoms.push_back(Vector3d<T>(points[i], -height * 0.5));
	}
	std::vector<Curve3d<T>> curves;
//	Curve3d<T> topCurve(tops);
//	Curve3d<T> bottomCurve(bottoms);
	return curves;
	//getBotton().to;
}


/*
template<typename T>
T Cylinder<T>::getRadius() const
{

}
*/

template class Cylinder<float>;
template class Cylinder<double>;