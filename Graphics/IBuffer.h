#ifndef __CRYSTAL_GRAPHICS_BUFFER_H__
#define __CRYSTAL_GRAPHICS_BUFFER_H__

#include <vector>

namespace Crystal {
	namespace Graphics {

template<typename T>
class IBuffer
{
public:
	IBuffer() = default;

	IBuffer(const std::vector<T>& buffer) : buffer( buffer)
	{}

	virtual ~IBuffer() = default;


	void clear() { buffer.clear(); }



	std::vector< T > get() const { return buffer; }

protected:
	std::vector< T > buffer;
};


	}
}

#endif