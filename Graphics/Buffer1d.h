#ifndef __CRYSTAL_GRAPHICS_BUFFER_1D_H__
#define __CRYSTAL_GRAPHICS_BUFFER_1D_H__

#include "IBuffer.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class Buffer1d : public IBuffer<T> {
public:
	Buffer1d() = default;

	Buffer1d(const std::vector<T>& buffer) :
		IBuffer(buffer)
	{}

	~Buffer1d() = default;

	void add(const T v) { buffer.push_back(v); }

	T get(const unsigned int i) const { return buffer.get[i]; }

	std::vector< T > get() const { return buffer; }


private:
};

	}
}

#endif