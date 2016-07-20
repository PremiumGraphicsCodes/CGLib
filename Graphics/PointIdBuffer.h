#ifndef __CRYSTAL_GRAPHICS_POINT_ID_BUFFER_H__
#define __CRYSTAL_GRAPHICS_POINT_ID_BUFFER_H__

#include "Buffer1d.h"
#include "Buffer3d.h"
#include "Buffer4d.h"
#include "DrawableID.h"

namespace Crystal {
	namespace Graphics {

class PointIdBuffer
{
public:
	PointIdBuffer() = default;

	void clear();

	void add(const Math::Vector3d<float>& position, const float size, const DrawableID did);

	Graphics::Buffer3d<float> getPosition() const { return position; }

	Graphics::Buffer4d<float> getIdColor() const { return idColor; }

	Graphics::Buffer1d<float> getSize() const { return sizes; }

private:
	Graphics::Buffer3d<float> position;
	Graphics::Buffer4d<float> idColor;
	Graphics::Buffer1d<float> sizes;
};
	}
}

#endif