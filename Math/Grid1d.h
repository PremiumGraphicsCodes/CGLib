#ifndef __CRYSTAL_MATH_GRID_1D_H__
#define __CRYSTAL_MATH_GRID_1D_H__

#include <vector>

namespace Crystal {
	namespace Math {

template<typename T>
class Grid1d final
{
public:
	Grid1d() = default;

	explicit Grid1d(const size_t size) :values(size)
	{}

	explicit Grid1d(const std::vector<T>& values) :
		values(values)
	{}

	Grid1d(const size_t size, const T v) : values(size, v)
	{}

	~Grid1d() = default;

	size_t getSize() const { return values.size(); }

	T get(const size_t i) const { return values[i]; }

	void set(const size_t i, const T v) { values[i] = v; }

	void set(const unsigned int start, const Grid1d& rhs);

	Grid1d getSub(const size_t startIndex, const size_t endIndex) const;

	bool equals(const Grid1d& rhs) const { return values == rhs.values; }

	bool operator==(const Grid1d& rhs) const { return equals(rhs); }

	bool operator!=(const Grid1d& rhs) const { return !equals(rhs); }

	bool isValidIndex(const int index) const { return (0 <= index) && (index < static_cast<int>(values.size())); }

private:
	std::vector< T > values;
};

	}
}

#endif