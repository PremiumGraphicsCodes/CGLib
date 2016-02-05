#ifndef __CRYSTAL_MATH_QUAD_H__
#define __CRYSTAL_MATH_QUAD_H__

#include "Vector3d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Quad
{
public:
	Quad(const std::array<Vector3d<T>, 4>& positions) :
		positions(positions)
	{}

	Math::Vector3d<T> getNormal() const {
		const auto v1 = positions[1] - positions[0];
		const auto v2 = positions[2] - positions[0];
		return v1.getOuterProduct(v2);
	}

	std::array<Vector3d<T>, 4> getPositions() const { return positions; }

private:
	std::array<Vector3d<T>, 4> positions;
};
	}
}

#endif