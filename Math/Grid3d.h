#ifndef __CRYSTAL_MATH_GRID_H__
#define __CRYSTAL_MATH_GRID_H__

#include "Grid1d.h"
#include "Grid2d.h"
#include "Index3d.h"

#include <vector>
#include <array>


namespace Crystal {
	namespace Math{

template<typename>
class Vector3d;

template<typename T>
class Grid3d final
{
public:
	Grid3d() = default;

	~Grid3d() = default;

	Grid3d(const size_t sizex, const size_t sizey, const size_t sizez, const T value = { 0 });

	Grid3d(const Index3d resolution, const T value = { 0 }) :
		Grid3d(resolution.getX(), resolution.getY(), resolution.getZ(), value)
	{}

	//Grid3d(const size_t sizex, const size_t sizey, const size_t sizez, const float value);

	explicit Grid3d(const Grid2dVector<T>& grids);

	Grid3d(const Grid2d<T>& grid2ds, const int howMany);

	T get(const size_t x, const size_t y, const size_t z) const { return grids[z].get(x,y); }

	void fill(const T v);

	void set(const size_t x, const size_t y, const size_t z, const T v) { grids[z].set(x, y, v); }

	int getSizeX() const { return static_cast<int>(grids.front().getSizeX()); }

	int getSizeY() const { return static_cast<int>(grids.front().getSizeY()); }

	int getSizeZ() const { return static_cast<int>(grids.size()); }

	std::array<int,3> getSizes() const { return { getSizeX(), getSizeY(), getSizeZ() }; }

	void add(const size_t x, const size_t y, const size_t z, const T v);

	void sub(const size_t x, const size_t y, const size_t z, const T v) { add( x, y, z, -v ); }

	void add(const Grid3d& rhs, const Index3d startIndex);

	void sub(const Grid3d& rhs, const Index3d startIndex);

	void mul(const Grid3d& rhs);

	void not();

	void move(const int x, const int y, const int z);

	void scale(const float xscale, const float yscale, const float zscale);

	void set(const std::array<unsigned int, 3>& start, const Grid3d& rhs);

	std::array< T, 8 > toArray8(const size_t i, const size_t j, const size_t k) const;

	bool isAllLower(const size_t i, const size_t j, const size_t k, const T t) const;

	bool isAllHigher(const size_t i, const size_t j, const size_t k, const T t) const;

	bool isNotBoundary(const size_t i, const size_t j, const size_t k, const T threshold) const;

	bool isBoundary(const size_t i, const size_t j, const size_t k, const T threshold) const { return !isNotBoundary(i, j, k, threshold); }

	bool isLower(const size_t i , const size_t j, const size_t k ,const T threshold) const { return (get(i, j, k) < threshold); }

	bool isHigher(const size_t i, const size_t j, const size_t k, const T threshold) const { return !isLower(i, j, k, threshold); }

	bool equals(const Grid3d& rhs) const { return grids == rhs.grids; }

	bool operator==(const Grid3d& rhs) const { return equals(rhs); }

	bool operator!=(const Grid3d& rhs) const { return !equals(rhs); }

	bool isValidIndex(const Index3d index) const;

	bool isValidIndex(const int x, const int y, const int z) const;

	Math::Vector3d<T> getLocalCoord(const Index3d index) const;

	Grid3d<T> createRotateX();

	Grid3d<T> createRotateY();

	//Grid3d<T> createRotateZ();

private:
	Grid2dVector<T> grids;
};

	}
}

#endif