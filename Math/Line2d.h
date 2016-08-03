#ifndef __CRYSTAL_MATH_LINE_2D_H__
#define __CRYSTAL_MATH_LINE_2D_H__

#include "Vector2d.h"

#include <vector>

namespace Crystal {
	namespace Math {

template<typename T>
class Line2d
{
public:
	Line2d();

	Line2d(const Vector2d<T>& start, const Vector2d<T>& end);

	void move(const Vector2d<T>& v) { this->start += v; }

	void moveStartTo(const Vector2d<T>& p);

	void moveEndTo(const Vector2d<T>& p) { this->vector -= (getEnd() - p); }

	Vector2d<T> getStart() const { return start; }

	//Vector2d<T> getCenter() const { return start + vector * T(0.5); }

	Vector2d<T> getEnd() const { return start + vector; }

	//Vector2d<T> getPosition(const T param) const { return start + vector * param; }

	T getLength() const { return vector.getLength(); }

	bool equals(const Line2d<T>& rhs) const;

	bool operator==(const Line2d<T>& rhs) const { return equals(rhs); }

	bool operator!=(const Line2d<T>& rhs) const { return !equals(rhs); }

private:
	Vector2d<T> start;
	Vector2d<T> vector;
};

	}
}

#endif