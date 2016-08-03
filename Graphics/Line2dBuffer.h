#ifndef __CRYSTAL_GRAPHICS_LINE_2D_BUFFER_H__
#define __CRYSTAL_GRAPHICS_LINE_2D_BUFFER_H__

#include "Buffer3d.h"
#include "Buffer1d.h"
#include "Buffer4d.h"

#include "../Graphics/ColorRGBA.h"
#include "DrawableID.h"

namespace Crystal {
	namespace Graphics {

class Line2dBuffer
{
public:
	Line2dBuffer() = default;

	Line2dBuffer(const Math::Line2d<float>& line, const ColorRGBA<float>& color);

	void add(const Math::Line2d<float>& line, const ColorRGBA<float>& color);

	Graphics::Buffer3d<float> getPosition() const { return position; }

	Graphics::Buffer4d<float> getColor() const { return color; }

	std::vector<unsigned int> getIds() const { return ids; }

private:
	Buffer3d<float> position;
	Buffer4d<float> color;
	std::vector<unsigned int> ids;
};

	}
}

#endif