#ifndef __CRYSTAL_MATH_PARAMETER_H__
#define __CRYSTAL_MATH_PARAMETER_H__

namespace Crystal {
	namespace Math {

template<typename T>
class Angle;

template<typename T>
class Param
{
public:
	Param();

	explicit Param(T param);

	Angle<T> toAngle() const;

	T get() const { return param; }

private:
	bool isValid() const;

	T param;
};

	}
}

#endif