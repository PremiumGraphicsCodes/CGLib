#include "Grid3d.h"

#include <cassert>
#include <bitset>

using namespace Crystal::Math;

template<typename T>
Grid3d<T>::Grid3d(const size_t sizex, const size_t sizey, const size_t sizez) :
	grids(sizez, Grid2d<T>(sizex, sizey))
{}

template<typename T>
Grid3d<T>::Grid3d(const Grid2dVector<T>& grids) :
	grids(grids)
{}

/*
template<typename T>
Grid3d<T>::Grid3d(const size_t sizex, const size_t sizey, const size_t sizez, const float value)
{

}
*/


template<typename T>
void Grid3d<T>::fill(const T v)
{
	for (int i = 0; i < this->getSizeX(); ++i) {
		for (int j = 0; j < this->getSizeY(); ++j) {
			for (int k = 0; k < this->getSizeZ(); ++k) {
				this->set(i, j, k, v);
			}
		}
	}
}

template<typename T>
void Grid3d<T>::add(const size_t x, const size_t y, const size_t z, const T v)
{
	const auto vv = this->get(x, y, z) + v;
	this->set(x, y, z, vv);
}


template<typename T>
void Grid3d<T>::add(const Grid3d& rhs, const Index3d startIndex)
{
	for (auto x = startIndex[0]; x < getSizeX(); ++x) {
		for (auto y = startIndex[1]; y < getSizeY(); ++y) {
			for (auto z = startIndex[2]; z < getSizeZ(); ++z) {
				if (isValidIndex(startIndex)) {
					const auto v = rhs.get(x, y, z);
					add(x, y, z, v);
				}
			}
		}
	}
}

template<typename T>
void Grid3d<T>::sub(const Grid3d& rhs, const Index3d startIndex)
{
	for (auto x = startIndex[0]; x < getSizeX(); ++x) {
		for (auto y = startIndex[1]; y < getSizeY(); ++y) {
			for (auto z = startIndex[2]; z < getSizeZ(); ++z) {
				if (isValidIndex(startIndex)) {
					const auto v = rhs.get(x, y, z);
					sub(x, y, z, v);
				}
			}
		}
	}
}


template<typename T>
void Grid3d<T>::set(const std::array<unsigned int, 3>& start, const Grid3d& rhs)
{
	for (auto x = 0; x < rhs.getSizeX(); ++x) {
		for (auto y = 0; y < rhs.getSizeY(); ++y) {
			for (auto z = 0; z < rhs.getSizeZ(); ++z) {
				const T v = rhs.get(x, y, z);
				set(x + start[0], y + start[1], z + start[2], v);
			}
		}
	}
}


template<typename T>
void Grid3d<T>::mul(const Grid3d& rhs)
{
	for (auto x = 0; x < getSizeX(); ++x) {
		for (auto y = 0; y < getSizeY(); ++y) {
			for (auto z = 0; z < getSizeZ(); ++z) {
				const auto v = rhs.get(x, y, z);
				const auto vv = this->get(x, y, z);
				this->set(x, y, z, v *vv);
			}
		}
	}
}

template<typename T>
void Grid3d<T>::not()
{
	T max_ = 1;
	for (int x = 0; x < getSizeX(); ++x) {
		for (int y = 0; y < getSizeY(); ++y) {
			for (int z = 0; z < getSizeZ(); ++z) {
				const auto v = get(x, y, z);
				this->set(x, y, z, max_ - v);
			}
		}
	}
}

template<typename T>
void Grid3d<T>::move(const int diffx, const int diffy, const int diffz)
{
	Grid3d<T> newGrid(getSizeX(), getSizeY(), getSizeZ());
	for (int x = 0; x < getSizeX(); ++x) {
		for (int y = 0; y < getSizeY(); ++y) {
			for (int z = 0; z < getSizeZ(); ++z) {
				const auto v = get(x, y, z);
				const auto destx = x + diffx;
				const auto desty = y + diffy;
				const auto destz = z + diffz;
				if (newGrid.isValidIndex(destx, desty, destz)) {
					newGrid.set(destx, desty, destz, v);
				}
			}
		}
	}
	*this = newGrid;
}

#include "Vector3d.h"

template<typename T>
void Grid3d<T>::scale(const float xscale, const float yscale, const float zscale)
{
	/*
	const auto centerx = this->getSizeX() * 0.5f;
	const auto centery = this->getSizeY() * 0.5f;
	const auto centerz = this->getSizeZ() * 0.5f;
	Vector3d<float> center(centerx, centery, centerz);
	Grid3d<T> newGrid(getSizeX(), getSizeY(), getSizeZ());
	for (int x = 0; x < getSizeX(); ++x) {
		for (int y = 0; y < getSizeY(); ++y) {
			for (int z = 0; z < getSizeZ(); ++z) {
				Vector3d<float> v(x,y,z);
				Vector3d<float> pos = v - center;
				/*
				const auto v = get(x, y, z);
				const auto destx = x + diffx;
				const auto desty = y + diffy;
				const auto destz = z + diffz;
				if (newGrid.isValidIndex(destx, desty, destz)) {
					newGrid.set(destx, desty, destz, v);
				}
			}
		}
	}
	*this = newGrid;
*/
}


template<typename T>
bool Grid3d<T>::isAllHigher(const size_t i, const size_t j, const size_t k, const T t) const
{
	assert(i < getSizeX() && j < getSizeY() && k < getSizeZ());
	std::bitset<8> bs;
	bs.set(0, isHigher(i, j, k, t));
	bs.set(1, isHigher(i + 1, j, k, t));
	bs.set(2, isHigher(i + 1, j + 1, k, t));
	bs.set(3, isHigher(i, j + 1, k, t));
	bs.set(4, isHigher(i, j, k + 1, t));
	bs.set(5, isHigher(i + 1, j, k + 1, t));
	bs.set(6, isHigher(i + 1, j + 1, k + 1, t));
	bs.set(7, isHigher(i, j + 1, k + 1, t));
	return (bs.all());
}

template<typename T>
bool Grid3d<T>::isAllLower(const size_t i, const size_t j, const size_t k, const T t) const
{
	assert(i < getSizeX() && j < getSizeY() && k < getSizeZ());
	std::bitset<8> bs;
	bs.set(0, isLower(i, j, k, t));
	bs.set(1, isLower(i + 1, j, k, t));
	bs.set(2, isLower(i + 1, j + 1, k, t));
	bs.set(3, isLower(i, j + 1, k, t));
	bs.set(4, isLower(i, j, k + 1, t));
	bs.set(5, isLower(i + 1, j, k + 1, t));
	bs.set(6, isLower(i + 1, j + 1, k + 1, t));
	bs.set(7, isLower(i, j + 1, k + 1, t));
	return (bs.all());
}

template<typename T>
bool Grid3d<T>::isNotBoundary(const size_t i, const size_t j, const size_t k, const T threshold) const
{
	return isAllLower(i, j, k, threshold) || isAllHigher(i, j, k, threshold);
}

template<typename T>
std::array< T, 8 > Grid3d<T>::toArray8(const size_t i, const size_t j, const size_t k) const
{
	return std::array < T, 8 > {
		get(i, j, k),
		get(i + 1, j, k),
		get(i + 1, j + 1, k),
		get(i, j + 1, k),
		get(i, j, k + 1),
		get(i + 1, j, k + 1),
		get(i + 1, j + 1, k + 1),
		get(i, j + 1, k + 1)
	};
}

template<typename T>
bool Grid3d<T>::isValidIndex(const Index3d index) const
{
	return isValidIndex(index[0], index[1], index[2]);
}

template<typename T>
bool Grid3d<T>::isValidIndex(const int x, const int y, const int z) const
{
	return
		(0 <= x && x < static_cast<int>(getSizeX())) &&
		(0 <= y && y < static_cast<int>(getSizeY())) &&
		(0 <= z && z < static_cast<int>(getSizeZ()));
}

template<typename T>
Vector3d<T> Grid3d<T>::getLocalCoord(const Index3d index) const
{
	const Vector3d<T> start(-0.5, -0.5, -0.5);

	const Vector3d<T> lengths(T{ 1.0 } / this->getSizeX(), T{ 1.0 } / this->getSizeY(), T{ 1.0 } / this->getSizeZ());
	const Vector3d<T> result = start + lengths.getScaled(
		static_cast<T>(index[0]),
		static_cast<T>(index[1]),
		static_cast<T>(index[2]));
	return result;
}

template class Grid3d<float>;
template class Grid3d<double>;