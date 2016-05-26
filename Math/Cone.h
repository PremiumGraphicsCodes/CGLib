#ifndef __CRYSTAL_MATH_CONE_H__
#define __CRYSTAL_MATH_CONE_H__

namespace Crystal {
	namespace Math {

template<typename T>
class Cone
{
public:
	Cone();

	Cone(const T radius, const T height);

	T getVolume() const;

	T getRadius() const { return radius; }

	T getHeight() const { return height; }


private:
	T radius;
	T height;
};
	}
}

#endif