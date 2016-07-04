#ifndef __CRYSTAL_MATH_POINT_3D_H__
#define __CRYSTAL_MATH_POINT_3D_H__

#include "Vector2d.h"
#include "Vector3d.h"
#include "Point2d.h"
#include "Matrix3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Point3d
{
public:
	Point3d() = default;

	explicit Point3d(const Point2d<T>& point2d);

	explicit Point3d(const Vector3d<T>& position);

	Point3d(const Vector3d<T>& position, const Vector3d<T>& normal);

	Point3d(const Vector3d<T>& position, const Vector3d<T>& normal, const Vector2d<T>& parameter);

	virtual ~Point3d() {};

	Vector3d<T> getPosition() const { return position; }

	void setNormal(const Math::Vector3d<T>& n) { this->normal = n; }

	Vector3d<T> getNormal() const { return normal; }

	Vector2d<T> getParameter() const { return parameter; }

	void move(const Vector3d<T>& v) { this->position += v; }

	void moveTo(const Vector3d<T>& v) { this->position = v; }

	void transform(const Matrix3d<T>& m);

	void scale(const Math::Vector3d<T>& m);

	bool operator==(const Point3d<T>& rhs) const {
		return this->position == rhs.position &&
			this->normal == rhs.normal &&
			this->parameter == rhs.parameter;
	}

	Point3d lerp(const Point3d& rhs, const T param) const;

	Point3d clone() const { return Point3d<T>(position, normal, parameter); }


private:
	Math::Vector3d<T> position;
	Math::Vector3d<T> normal;
	Math::Vector2d<T> parameter;
};
	}
}

#endif