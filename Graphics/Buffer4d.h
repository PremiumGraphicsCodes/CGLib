#ifndef __CRYSTAL_GRAPHICS_BUFFER_4D_H__
#define __CRYSTAL_GRAPHICS_BUFFER_4D_H__

#include "ColorRGBA.h"
#include "IBuffer.h"
#include "../Math/Quaternion.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class Buffer4d : public IBuffer<T> {
public:
	Buffer4d() = default;

	Buffer4d(const std::vector<T>& buffer) :
		IBuffer(buffer)
	{}

	~Buffer4d() = default;

	void add(const Graphics::ColorRGBA<T>& v) {
		buffer.push_back(v.getRed());
		buffer.push_back(v.getGreen());
		buffer.push_back(v.getBlue());
		buffer.push_back(v.getAlpha());
	}

	void add(const Buffer4d<T>& rhs) {
		buffer.insert(buffer.end(), rhs.buffer.begin(), rhs.buffer.end());
	}

	void add(const Math::Quaternion<T>& q) {
		buffer.push_back(q.getX());
		buffer.push_back(q.getY());
		buffer.push_back(q.getZ());
		buffer.push_back(q.getW());
	}

	bool operator==(const Buffer4d<T>& rhs) { return buffer == rhs.buffer; }

	std::vector< T > get() const { return buffer; }


private:
};

	}
}

#endif