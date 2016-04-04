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

	Math::Vector3d<T> getNormal() const;

	//std::vector< Math::Vector3d<T> > toInnerPoints() const;

	std::array<Vector3d<T>, 4> getPositions() const { return positions; }

private:
	std::array<Vector3d<T>, 4> positions;
};
	}
}

#endif