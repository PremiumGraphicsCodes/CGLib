#ifndef __CRYSTAL_MATH_TRIANGLE_CURVE_3D_H__
#define __CRYSTAL_MATH_TRIANGLE_CURVE_3D_H__

#include "Vector3d.h"
#include "Point3d.h"
#include "Curve2d.h"
#include "../Util/Array2d.h"
//#include "TriangleCell.h"
#include <vector>

namespace Crystal {
	namespace Math {

template<typename T>
class TriangleCurve3d
{
public:
	TriangleCurve3d() = default;

	TriangleCurve3d(const int num);

	Point3d<T> get(const int u, const int v) const;

	void set(const int u, const int v, const Point3d<T>& point);

	//void move(const Vector3d<T>& v);

	//void transform(const Matrix3d<T>& matrix);

	size_t getSize() const { return points.size(); }

	//TriangleCell<T> toCells() const;

private:
	//std::vector< std::vector< Point3d<T> > > points;
	std::vector< std::vector<Point3d<T>> > points;
};
	}
}


#endif