#ifndef __CRYSTAL_MATH_GRID_2D_H__
#define __CRYSTAL_MATH_GRID_2D_H__

#include "Grid1d.h"

namespace Crystal {
	namespace Math {

template<typename T>
class Grid2d final
{
public:
	Grid2d() = default;

	Grid2d(const size_t sizex, const size_t sizey);

	explicit Grid2d(const std::vector<Grid1d<T>>& grids) :
		grids(grids)
	{}

	T get(const size_t x, const size_t y) const { return grids[y].get(x); }

	void set(const size_t x, const size_t y, const T v) { grids[y].set(x, v); }

	size_t getSizeX() const { return grids.front().getSize(); }

	size_t getSizeY() const { return grids.size(); }

	Grid2d getSub(const size_t startx, const size_t endx, const size_t starty, const size_t endy) const {
		std::vector<Grid1d<T>> gs(grids.begin() + starty, grids.begin() + endy);
		for (auto& g : gs) {
			g = g.getSub(startx, endx);
		}
		return Grid2d(gs);
	}

	bool equals(const Grid2d& rhs) const { return grids == rhs.grids; }

	bool operator==(const Grid2d& rhs) const { return equals(rhs); }

	bool operator!=(const Grid2d& rhs) const { return !equals(rhs); }

	bool isValidIndex(const int x, const int y) const {
		return
			(0 <= x && x < static_cast<int>(getSizeX())) &&
			(0 <= y && y < static_cast<int>(getSizeY()));
	}

	
private:
	std::vector< Grid1d<T> > grids;
};

template<typename T>
using Grid2dVector = std::vector < Grid2d<T> >;

	}
}

#endif