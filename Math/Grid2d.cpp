#include "Grid2d.h"

using namespace Crystal::Math;

template<typename T>
Grid2d<T>::Grid2d(const size_t sizex, const size_t sizey) :
	grids(sizey, Grid1d<T>(sizex))
{}


template class Grid2d<unsigned char>;
template class Grid2d<float>;
template class Grid2d<double>;