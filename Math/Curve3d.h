#ifndef __CRYSTAL_MATH_CURVE_3D_H__
#define __CRYSTAL_MATH_CURVE_3D_H__

#include "Vector3d.h"
#include "Point.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Curve3d
{
public:
	Curve3d();

	Curve3d(const int uNum, const int vNum);

	Point<T> get(const int u, const int v) const;

	void set(const int u, const int v, const Point<T>& point);

	int getUNumber() const { return uNumber; }

	int getVNumber() const { return vNumber; }

private:
	std::vector< std::vector< Point<T> > > points;
	int uNumber;
	int vNumber;
};
	}
}


#endif