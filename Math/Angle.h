#ifndef __CRYSTAL_MATH_ANGLE_H__
#define __CRYSTAL_MATH_ANGLE_H__

#include "Degree.h"
#include "Radian.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Radian;



template<typename T>
class Angle
{
public:
	Angle();

	explicit Angle(const Degree<T> deg);

	explicit Angle(const Radian<T> rad);

	Degree<T> getDegree() const { return deg; }

	Radian<T> getRadian() const { return deg.toRadian(); }

	bool equals(const Angle<T> rhs) const;

	bool operator==(const Angle<T> rhs) const;

	bool operator!=(const Angle<T> rhs) const;

	bool operator<(const Angle<T> rhs) const;

	bool operator>(const Angle<T> rhs) const;

	Angle<T> operator-() const { return Angle<T>(-deg); }

	Angle<T> operator-(const Angle<T>& rhs) const { return Angle<T>(deg - rhs.deg); }

	//static T getZero() { return T{ 0 }; }

	static Angle<T> Zero();

	static Angle<T> HalfPI();

	static Angle<T> PI();

	static Angle<T> DoublePI();


	//T getX() const;

	//T getY() const;

	T getSin() const;

	T getCos() const;

private:
	Degree<T> deg;
};
	}
}

#endif