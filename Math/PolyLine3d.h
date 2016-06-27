#ifndef __CRYSTAL_MATH_POLY_LINE_3D_H__
#define __CRYSTAL_MATH_POLY_LINE_3D_H__

#include "Vector3d.h"

namespace Crystal {
	namespace Math {
		template<typename T>
		class Line3d;

template<typename T>
class Polyline3d
{
public:
	Polyline3d();

	Polyline3d(const std::vector<Vector3d<T>>& positions);

	void add(const Vector3d<T>& v) { this->positions.push_back(v); }

	std::vector<Math::Line3d<T>> toLines() const;

	std::vector<Vector3d<T>> getPositions() const;

	bool equals(const Polyline3d<T>& rhs) const;

	bool operator==(const Polyline3d<T>& rhs) const;

	bool operator!=(const Polyline3d<T>& rhs) const;

	size_t size() const { return positions.size(); }

private:
	std::vector<Vector3d<T>> positions;
};
	}
}

#endif