#ifndef __CRYSTAL_UTIL_ARRAY_2D_H__
#define __CRYSTAL_UTIL_ARRAY_2D_H__

#include <vector>

namespace Crystal {

template<typename T>
class Array2d
{
public:
	Array2d() :
		sizex(0), sizey(0)
	{}

	Array2d(const int sizex, const int sizey) :
		sizex(sizex),
		sizey(sizey),
		values(sizex * sizey)
	{
	}

	//T get(int x, int y) {sizex * x + y}
	int toIndex1d(const int x, const int y) const { return sizex * y + x; }

	T get(const int x, const int y) const { return values[toIndex1d(x, y)]; }

	T& get(const int x, const int y) { return values[toIndex1d(x, y)]; }

	void set(const int x, const int y, const T v) {
		values[toIndex1d(x,y)] = v;
	}

	int getSizeX() const { return sizex; }

	int getSizeY() const { return sizey; }

private:
	const int sizex;
	const int sizey;
	std::vector<T> values;
};

}

#endif