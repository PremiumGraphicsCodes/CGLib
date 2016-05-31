#ifndef __CRYSTAL_MATH_CYLINDER_H__
#define __CRYSTAL_MATH_CYLINDER_H__

namespace Crystal {
	namespace Math {

template<typename T>
class Cylinder
{
public:
	Cylinder();

	Cylinder(const T radius, const T height);

	T getVolume() const;

	//T getRadius() const;

private:
	T radius;
	T height;
};
	}
}

#endif