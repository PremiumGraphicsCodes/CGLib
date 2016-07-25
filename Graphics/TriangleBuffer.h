#ifndef __CRYSTAL_GRAPHICS_TRIANGLE_BUFFER_H__
#define __CRYSTAL_GRAPHICS_TRIANGLE_BUFFER_H__

#include <vector>

#include "../Core/PolygonMesh.h"
#include "DrawableID.h"

#include "Buffer3d.h"
#include "Buffer4d.h"

namespace Crystal {
	namespace Core {
		class PolygonMesh;
		class Vertex;
	}
	namespace Graphics {

class TriangleBuffer
{
public:
	TriangleBuffer();

	TriangleBuffer(const Core::PolygonFactory& factory);

	void add(const Core::PolygonMesh& polygon);

	Buffer3d<float> getPositions() const { return positions; }

	Buffer3d<float> getNormals() const { return normals; }

	Buffer3d<float> getTexCoords() const { return texCoords; }

	std::vector<unsigned int> getIndices() const { return indices; }

private:
	std::vector<unsigned int> indices;
	Buffer3d<float> positions;
	Buffer3d<float> normals;
	Buffer3d<float> texCoords;
};

	}
}

#endif