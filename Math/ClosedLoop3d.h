#ifndef __CRYSTAL_MATH_CLOSED_LOOP_3D_H__
#define __CRYSTAL_MATH_CLOSED_LOOP_3D_H__

#include <array>
#include "Point3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class TriangleLoop3d
{
public:
	TriangleLoop3d(const std::array<Point3d<T>*, 3>& points) :
		points(points)
	{}
private:
	std::array<Point3d<T>*, 3> points;
};

template<typename T>
class ClosedLoop3d
{
public:
	ClosedLoop3d() = default;

	ClosedLoop3d(const std::vector<Point3d<T>*>& points);


private:
	std::vector<Point3d<T>*> points;
};
	}
}

#endif