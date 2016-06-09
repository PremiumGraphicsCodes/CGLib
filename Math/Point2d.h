#ifndef __CRYSTAL_MATH_POINT_2D_H__
#define __CRYSTAL_MATH_POINT_2D_H__

#include "Vector2d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Point2d
{
public:
	Point2d() = default;

	explicit Point2d(const Vector2d<T>& position);

	Point2d(const Vector2d<T>& position, const Vector2d<T>& normal);

	Point2d(const Vector2d<T>& position, const Vector2d<T>& normal, T parameter);

	virtual ~Point2d() {};

	Vector2d<T> getPosition() const { return position; }

	void setNormal(const Math::Vector2d<T>& n) { this->normal = n; }

	Vector2d<T> getNormal() const { return normal; }

	T getParameter() const { return parameter; }

private:
	Math::Vector2d<T> position;
	Math::Vector2d<T> normal;
	T parameter;
};
	}
}

#endif