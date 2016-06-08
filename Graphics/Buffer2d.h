#ifndef __CRYSTAL_GRAPHICS_BUFFER_2D_H__
#define __CRYSTAL_GRAPHICS_BUFFER_2D_H__

#include "../Math/Vector3d.h"

#include "IBuffer.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class Buffer2d : public IBuffer<T> {
public:
	Buffer2d() = default;

	Buffer2d(const std::vector<T>& buffer) :
		IBuffer(buffer)
	{}

	~Buffer2d() = default;

	void add(const Math::Vector2d<T>& v) {
		buffer.push_back(v.getX());
		buffer.push_back(v.getY());
	}

	Math::Vector2d<T> get(const unsigned int i) const {
		const auto x = buffer[i * 2];
		const auto y = buffer[i * 2 + 1];
		return Math::Vector2d<T>(x, y);
	}

	std::vector< T > get() const { return std::move(buffer); }

};

	}
}

#endif