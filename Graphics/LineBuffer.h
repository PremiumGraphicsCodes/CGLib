#ifndef __CRYSTAL_GRAPHICS_LINE_BUFFER_H__
#define __CRYSTAL_GRAPHICS_LINE_BUFFER_H__

#include "Buffer3d.h"
#include "Buffer1d.h"
#include "Buffer4d.h"

#include "../Math/Line3d.h"
#include "../Polygon/PolygonMesh.h"
#include "../Graphics/ColorRGBA.h"

namespace Crystal {
	namespace Polygon {
		class PolygonMesh;
		class Actor;
	}
	namespace Graphics {

class LineBuffer
{
public:
	void clear();

	void add(const Polygon::PolygonMesh& polygon, const ColorRGBA<float>& color);

	void add(const Math::Line3d<float>& line, const ColorRGBA<float>& color, const int id = 0);

	std::vector<IBuffer<float>> getBuffers() const {
		return{ position, color };
	}

	Graphics::Buffer3d<float> getPosition() const { return position; }

	Buffer4d<float> getIdColors() const { return idColors; }

	Graphics::Buffer4d<float> getColor() const { return color; }

	std::vector<unsigned int> getIds() const { return ids; }

private:
	Buffer3d<float> position;
	Buffer4d<float> idColors;
	Buffer4d<float> color;
	std::vector<unsigned int> ids;
};

	}
}

#endif