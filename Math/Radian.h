#ifndef __CRYSTAL_MATH_RADIAN_H__
#define __CRYSTAL_MATH_RADIAN_H__

namespace Crystal {
	namespace Math {

template<typename T>
class Degree;

template<typename T>
class Radian
{
public:
	Radian();

	explicit Radian(const T rad);

	Degree<T> toDegree() const;

	T get() const { return rad; }

	bool equals(const Radian<T> rhs) const;

	bool operator==(const Radian<T> rhs) const;

	bool operator!=(const Radian<T> rhs) const;

	Radian<T> operator-() const { return Radian<T>(-rad); }

private:
	T rad;
};

	}
}

#endif