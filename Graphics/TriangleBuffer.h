#ifndef __CRYSTAL_GRAPHICS_TRIANGLE_BUFFER_H__
#define __CRYSTAL_GRAPHICS_TRIANGLE_BUFFER_H__

#include <vector>

#include "../Math/Triangle.h"
#include "../Polygon/PolygonObject.h"

#include "Buffer3d.h"
#include "Buffer4d.h"

namespace Crystal {
	namespace Polygon {
		class PolygonObject;
		class Vertex;
	}
	namespace Graphics {

class TriangleBuffer
{
public:
	void add(const Polygon::PolygonObject& polygon);

	void add(const Polygon::Vertex& vertex, const Graphics::ColorRGBA<float>& color);

	void add(const Math::Triangle<float>& triangle);

	void clear();

	Buffer3d<float> getPositions() const { return positions; }
	Buffer3d<float> getNormals() const { return normals; }
	Buffer4d<float> getColors() const { return colors; }
	Buffer4d<float> idColors;
	std::vector<unsigned int> getIndices() const { return indices; }

	std::vector<unsigned int> getIndices(const unsigned int start, const unsigned int end) const;

private:
	std::vector<unsigned int> indices;
	Buffer3d<float> positions;
	Buffer3d<float> normals;
	Buffer4d<float> colors;
	unsigned int nextIndex;

};

	}
}

#endif