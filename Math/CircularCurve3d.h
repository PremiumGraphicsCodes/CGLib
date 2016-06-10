#ifndef __CRYSTAL_MATH_CIRCULAR_CURVE_3D_H__
#define __CRYSTAL_MATH_CIRCULAR_CURVE_3D_H__

#include "Vector3d.h"
#include "Point3d.h"
#include "Curve2d.h"
#include "../Util/Array2d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class CircularCurve3d
{
public:
	CircularCurve3d();

	CircularCurve3d(const Point2d<T>& center, const Curve2d<T>& curve2d);

	CircularCurve3d(const Point3d<T>& center,const std::vector<Point3d<T>>& points);

	Point3d<T> get(const int u) const;

	void move(const Vector3d<T>& v);

	void transform(const Matrix3d<T>& matrix);

	size_t getSize() const { return  points.size(); }

	Point3d<T> getCenter() const { return center; }

private:
	std::vector<Point3d<T>> points;
	Point3d<T> center;
};
	}
}


#endif