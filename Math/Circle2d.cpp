#include "Circle2d.h"

#include "Tolerance.h"
#include "Angle.h"

using namespace Crystal::Math;

template<typename T>
Circle2d<T>::Circle2d() :
	radius(0.5)
{}

template<typename T>
Circle2d<T>::Circle2d(const T radius) :
	radius(radius)
{}

template<typename T>
T Circle2d<T>::getArea() const
{
	return radius * radius * Tolerance<T>::getPI();
}

template<typename T>
std::vector<Vector2d<T>> Circle2d<T>::toPoints(const int number) const
{
	std::vector<Vector2d<T>> points;
	for (int i = 0; i < number; ++i) {
		Degree<T> degree(T{ 360 } / number * i);
		Angle<T> angle(degree);
		const auto radian = angle.getRadian(); //angle * Tolerance<T>::getPI() / 180.0f;
		T x = ::sin(radian.get());
		T y = ::cos(radian.get());
		points.emplace_back(Vector2d<T>(x, y));
	}
	return points;
}


template class Circle2d<float>;
template class Circle2d<double>;