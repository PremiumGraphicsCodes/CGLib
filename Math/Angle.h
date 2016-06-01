#ifndef __CRYSTAL_MATH_ANGLE_H__
#define __CRYSTAL_MATH_ANGLE_H__

namespace Crystal {
	namespace Math {

template<typename T>
class Radian;

template<typename T>
class Degree
{
public:
	Degree();

	explicit Degree(const T deg);

	Radian<T> toRadian() const;

	T get() const { return deg; }

	bool equals(const Degree<T> rhs) const;

	bool operator==(const Degree<T> rhs) const;

	bool operator!=(const Degree<T> rhs) const;

private:
	T deg;
};

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

private:
	T rad;
};

template<typename T>
class Angle
{
public:
	Angle();

	explicit Angle(const Degree<T> deg);

	explicit Angle(const Radian<T> rad);

	Degree<T> getDegree() const { return deg; }

	Radian<T> getRadian() const { return deg.toRadian(); }

	bool equals(const Degree<T> rhs) const;

	bool operator==(const Degree<T> rhs) const;

	bool operator!=(const Degree<T> rhs) const;

	static T getPI();

	T getX() const;

	T getY() const;

private:
	Degree<T> deg;
};
	}
}

#endif