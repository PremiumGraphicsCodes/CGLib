#include "Circle2d.h"

#include "Tolerance.h"
#include "Angle.h"

using namespace Crystal::Math;

template<typename T>
Circle2d<T>::Circle2d() :
	radius(0.5),
	center(Vector2d<T>(0,0))
{}

template<typename T>
Circle2d<T>::Circle2d(const T radius) :
	radius(radius),
	center(Vector2d<T>(0, 0))
{}

template<typename T>
T Circle2d<T>::getArea() const
{
	return radius * radius * Tolerance<T>::getPI();
}

template<typename T>
Vector2d<T> Circle2d<T>::getPosition(const Angle<T> angle) const
{
	const auto radian = angle.getRadian(); //angle * Tolerance<T>::getPI() / 180.0f;
	T x = radius * ::sin(radian.get());
	T y = radius * ::cos(radian.get());
	return Vector2d<T>(x, y) + center;
}

template<typename T>
Vector2d<T> Circle2d<T>::getNormal(const Angle<T> angle) const
{
	return getPosition(angle) - center;
}

template<typename T>
Point2d<T> Circle2d<T>::getPoint(const Angle<T> angle) const
{
	const auto& position = getPosition(angle);
	const auto& normal = getNormal(angle);
	const auto param = angle.getDegree().get() / T{ 360 };
	return Point2d<T>(position, normal, param);
}

template<typename T>
Curve2d<T> Circle2d<T>::toCurve2d(const int number) const
{
	std::vector<Point2d<T>> points;
	for (int i = 0; i < number; ++i) {
		Degree<T> degree(T{ 360 } / number * i);
		Angle<T> angle(degree);
		points.emplace_back(getPoint(angle));
	}
	return Curve2d<T>(points);
}


template class Circle2d<float>;
template class Circle2d<double>;