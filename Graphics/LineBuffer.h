#ifndef __CRYSTAL_GRAPHICS_LINE_BUFFER_H__
#define __CRYSTAL_GRAPHICS_LINE_BUFFER_H__

#include "Buffer3d.h"
#include "Buffer1d.h"
#include "Buffer4d.h"

#include "../Graphics/ColorRGBA.h"
#include "DrawableID.h"

namespace Crystal {
	namespace Core {
		class PolygonMesh;
		class Actor;
	}
	namespace Graphics {

class LineBuffer
{
public:
	LineBuffer() = default;


	LineBuffer(const Math::Line3d<float>& line, const ColorRGBA<float>& color) {
		add(line, color);
	}

	LineBuffer(const Math::Polyline3d<float>& polyline, const ColorRGBA<float>& color);

	void clear();

	void add(const Math::Polyline3d<float>& polyline, const ColorRGBA<float>& color);

	void add(const Math::Point3d<float>& point, const ColorRGBA<float>& color);

	void add(const Core::Edge& edge, const ColorRGBA<float>& color);

	void add(const Core::PolygonMesh& polygon, const ColorRGBA<float>& color);

	void add(const Math::Line3d<float>& line, const ColorRGBA<float>& color);

	void add(const Core::PolygonFactory& factory);

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