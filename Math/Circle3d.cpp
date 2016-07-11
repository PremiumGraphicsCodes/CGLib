#include "Circle3d.h"
#include "PolyLine3d.h"

using namespace Crystal::Math;

template<typename T>
Circle3d<T>::Circle3d():
	radius(0.5)
{
}

template<typename T>
Circle3d<T>::Circle3d(const T radius,const Vector3d<T>& center, const Quaternion<T>& orientation) :
	IPrimitive3d<T>(center, orientation),
	radius(radius)
{
}

template<typename T>
bool Circle3d<T>::equals(const Circle3d<T>& rhs) const
{
	return
		radius == rhs.radius &&
		center == rhs.center &&
		orientation == rhs.orientation;
}

template<typename T>
bool Circle3d<T>::operator==(const Circle3d<T>& rhs) const
{
	return equals(rhs);
}

template<typename T>
bool Circle3d<T>::operator!=(const Circle3d<T>& rhs) const
{
	return !equals(rhs);
}

template<typename T>
Vector3d<T> Circle3d<T>::getPosition(const Angle<T> angle) const
{
	const auto x = radius * angle.getCos();
	const auto y = radius * angle.getSin();

	Vector3d<T> vec(x, y, 0);
	const auto rotation = orientation.toMatrix();
	vec.rotate(rotation.transposed());

	return vec + center;
}

template<typename T>
Vector3d<T> Circle3d<T>::getPosition(const Param<T> param) const
{
	Angle<T> angle(Degree<T>(param.get() * 360));
	return getPosition(angle);
}

template<typename T>
Point3d<T> Circle3d<T>::getPoint(const Param<T> param) const
{
	auto pos = getPosition(param);
	Vector3d<T> norm(0, 0, 1);
	Vector2d<T> p(0, 0);
	return Point3d<T>(pos, norm, p);
}


template<typename T>
Polyline3d<T> Circle3d<T>::toPolyline(const int number) const
{
	Polyline3d<T> polyline;
	for (int i = 0; i < number; ++i) {
		polyline.add( getPosition( Param<T>( i / (T)number) ) );
	}
	return polyline;
}

template<typename T>
CircularCurve3d<T> Circle3d<T>::toCurve(const int number) const
{
	//for (int i = 0; i < number; ++i) {
	std::vector<Point3d<T>> positions;
	for (int i = 0; i < number; ++i) {
		positions.push_back(getPoint(Param<T>(i / (T)number)));
	}

	Point3d<T> centerPoint(getCenter(), Vector3d<T>(0, 0, 1));
	CircularCurve3d<T> curve(centerPoint, positions);
	return curve;
}


template class Circle3d<float>;
template class Circle3d<double>;