#ifndef __CRYSTAL_GRAPHICS_LINE_BUFFER_H__
#define __CRYSTAL_GRAPHICS_LINE_BUFFER_H__

#include "Buffer3d.h"
#include "Buffer1d.h"
#include "Buffer4d.h"

#include "../Math/Line3d.h"

namespace Crystal {
	namespace Graphics {

class Line
{
public:
	Line(const Math::Line3d<float>& line, const ColorRGBA<float>& color) :
		line(line),
		color(color)
	{}

	Math::Line3d<float> getLine() const { return line; }

	ColorRGBA<float> getColor() const { return color; }

private:
	Math::Line3d<float> line;
	ColorRGBA<float> color;
};

struct LineBuffer
{
	void clear();

	void add(const Line& line);

	std::vector<IBuffer<float>> getBuffers() const {
		return{ position, color };
	}

private:
	Graphics::Buffer3d<float> position;
	Graphics::Buffer4d<float> color;
};

	}
}

#endif