#ifndef __CRYSTAL_MATH_INTERSECTION_H__
#define __CRYSTAL_MATH_INTERSECTION_H__

#include "Vector3d.h"
#include "Line3d.h"
#include "Triangle3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Intersection3d
{
public:
	Intersection3d();

	Intersection3d(const Line3d<T>& line, const Triangle3d<T>& triangle);

	bool hasIntersection() const { return !intersections.empty(); }

	std::vector<Vector3d<T>> getIntersections() const { return intersections; }


private:
	std::vector<Vector3d<T>> intersections;
};
	}
}

#endif