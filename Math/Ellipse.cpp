#include "Ellipse.h"

using namespace Crystal::Math;

template<typename T>
Ellipse<T>::Ellipse() :
	radii(Vector2d<T>(0.5,0.5))
{
}

template<typename T>
Ellipse<T>::Ellipse(const Vector2d<T>& radii) :
	radii(radii)
{
}

template<typename T>
T Ellipse<T>::getArea() const
{
	return radii.getX() * radii.getY() * Tolerance<T>::getPI();
}

template<typename T>
Vector2d<T> Ellipse<T>::getPosition(const Angle<T> angle) const
{
	T x = radii.getX() * angle.getCos();
	T y = radii.getY() * angle.getSin();
	return Vector2d<T>(x, y) + center;
}

template<typename T>
Vector2d<T> Ellipse<T>::getNormal(const Angle<T> angle) const
{
	const auto v = getPosition(angle) - center;
	return v.normalized();
}

template<typename T>
Point2d<T> Ellipse<T>::getPoint(const Angle<T> angle) const
{
	const auto& position = getPosition(angle);
	const auto& normal = getNormal(angle);
	const auto param = angle.getDegree().get() / T{ 360 };
	return Point2d<T>(position, normal, param);
}

template<typename T>
Curve2d<T> Ellipse<T>::toCurve2d(const int number) const
{
	std::vector<Point2d<T>> points;
	for (int i = 0; i < number; ++i) {
		Degree<T> degree(T{ 360 } / number * i);
		Angle<T> angle(degree);
		points.emplace_back(getPoint(angle));
	}
	return Curve2d<T>(points);
}

template class Ellipse<float>;
template class Ellipse<double>;