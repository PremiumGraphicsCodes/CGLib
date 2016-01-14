#ifndef __CRYSTAL_MATH_LINE_3D_H__
#define __CRYSTAL_MATH_LINE_3D_H__

#include "Vector3d.h"

#include <vector>

namespace Crystal {
	namespace Math {

template<typename T>
class Line3d final
{
public:
	Line3d();

	Line3d(const Vector3d<T>& start, const Vector3d<T>& end);

	void move(const Math::Vector3d<T>& v) { this->start += v; }

	void moveStartTo(const Math::Vector3d<T>& p);

	void moveEndTo(const Vector3d<T>& p) { this->vector -= (getEnd() - p); }

	Vector3d<T> getStart() const { return start; }

	Vector3d<T> getCenter() const { return start + vector * T(0.5); }

	Vector3d<T> getEnd() const { return start + vector; }

	Vector3d<T> getPosition(const T param) const { return start + vector * param; }

	T getLength() const { return vector.getLength(); }

	Vector3dVector<T> toPositionsByLength(const double divideLength) const;

	Vector3dVector<T> toPositionsByNumber(const unsigned int howMany) const;

	bool equals(const Line3d<T>& rhs) const;

	bool operator==(const Line3d<T>& rhs) const { return equals(rhs); }

	bool operator!=(const Line3d<T>& rhs) const { return !equals(rhs); }

private:
	Vector3d<T> start;
	Vector3d<T> vector;
};

	}
}

#endif