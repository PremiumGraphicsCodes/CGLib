#ifndef __CRYSTAL_MATH_INDEX_2D_H__
#define __CRYSTAL_MATH_INDEX_2D_H__

#include <array>

namespace Crystal {
	namespace Math {

class Index2d {
public:
	Index2d(const int x, const int y)
	{
		i[0] = x;
		i[1] = y;
	}

	Index2d(const std::array<int, 2>& i) : i(i)
	{}

	int operator[](int index) const { return i[index]; }

	int getX() const { return i[0]; }

	int getY() const { return i[1]; }

private:
	std::array < int, 2 > i;
};

	}
}
#endif