#ifndef __CRYSTAL_GRAPHICS_TRIANGLE_ID_BUFFER_H__
#define __CRYSTAL_GRAPHICS_TRIANGLE_ID_BUFFER_H__

#include <vector>

#include "../Core/PolygonMesh.h"

#include "Buffer3d.h"
#include "Buffer4d.h"

namespace Crystal {
	namespace Core {
		class Surface;
		class PolygonMesh;
		class Vertex;
	}
	namespace Graphics {

class TriangleIdBuffer
{
public:
	TriangleIdBuffer();

	void add(const Core::Surface& surface);

	void add(const Math::Point3d<float>& point, const int id);

	void clear();

	Buffer3d<float> getPositions() const { return positions; }

	Buffer4d<float> getIdColors() const { return idColors; }

	std::vector<unsigned int> getIndices() const { return indices; }

private:
	std::vector<unsigned int> indices;
	Buffer3d<float> positions;
	Buffer4d<float> idColors;
	unsigned int nextIndex;
};

	}
}

#endif