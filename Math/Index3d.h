#ifndef __CRYSTAL_MATH_INDEX_3D_H__
#define __CRYSTAL_MATH_INDEX_3D_H__

#include <array>

namespace Crystal {
	namespace Math {

class Index3d {
public:
	Index3d(const int x, const int y, const int z)
	{
		i[0] = x;
		i[1] = y;
		i[2] = z;
	}

	Index3d(const std::array<int, 3>& i) : i(i)
	{}

	int operator[](int index) const { return i[index]; }

	int getX() const { return i[0]; }

	int getY() const { return i[1]; }

	int getZ() const { return i[2]; }

private:
	std::array < int, 3 > i;
};

	}
}
#endif