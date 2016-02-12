#ifndef __CRYSTAL_GRAPHICS_LINE_BUFFER_H__
#define __CRYSTAL_GRAPHICS_LINE_BUFFER_H__

#include "Buffer3d.h"
#include "Buffer1d.h"
#include "Buffer4d.h"

#include "../Math/Line3d.h"
#include "../Polygon/PolygonObject.h"

namespace Crystal {
	namespace Polygon {
		class PolygonObject;
		class ActorObject;
	}
	namespace Graphics {

class LineBuffer
{
public:
	void clear();

	void add(const Polygon::PolygonObject& polygon);

	void add(const Polygon::ActorObject& actor);


	void add(const Math::Line3d<float>& line, const ColorRGBA<float>& color);

	std::vector<IBuffer<float>> getBuffers() const {
		return{ position, color };
	}

	Graphics::Buffer3d<float> getPosition() const { return position; }

	Graphics::Buffer4d<float> getColor() const { return color; }

	std::vector<unsigned int> getIds() const { return ids; }

private:
	Graphics::Buffer3d<float> position;
	Graphics::Buffer4d<float> color;
	std::vector<unsigned int> ids;
};

	}
}

#endif