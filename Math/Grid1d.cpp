#include "Grid1d.h"

using namespace Crystal::Math;

template<typename T>
void Grid1d<T>::set(const unsigned int start, const Grid1d& rhs)
{
	for (size_t x = 0; x < rhs.getSize(); ++x) {
		const T v = rhs.get(x);
		set(x + start, v);
	}
}

template<typename T>
Grid1d<T> Grid1d<T>::getSub(const size_t startIndex, const size_t endIndex) const
{
	std::vector<T> bs(values.begin() + startIndex, values.begin() + endIndex);
	return Grid1d(bs);
}


template class Grid1d<unsigned char>;
template class Grid1d<float>;
template class Grid1d<double>;