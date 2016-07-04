#ifndef __CRYSTAL_GRAPHICS_TRIANGLE_ID_BUFFER_H__
#define __CRYSTAL_GRAPHICS_TRIANGLE_ID_BUFFER_H__

#include <vector>

#include "../Core/PolygonMesh.h"

#include "Buffer3d.h"
#include "Buffer4d.h"

#include "DrawableID.h"

namespace Crystal {
	namespace Core {
		class Surface;
		class PolygonMesh;
		class Vertex;
	}
	namespace Graphics {

class TriangleIdBlock
{
public:
	TriangleIdBlock(const std::vector<unsigned int>& indices, const DrawableID& did) :
		indices(indices)
	{
		idColor.add(did.toColor());
	}

	std::vector<unsigned int> indices;
	Buffer4d<float> idColor;
};

class TriangleIdBuffer
{
public:
	TriangleIdBuffer();

	void add(const Core::Surface& surface, const DrawableID& did);

	void add(const Core::Surface& surface);

	void clear();

	Buffer3d<float> getPositions() const { return positions; }

	std::vector<TriangleIdBlock> getBlocks() const { return blocks; }

private:
	Buffer3d<float> positions;
	std::vector<TriangleIdBlock> blocks;
	unsigned int nextIndex;
};

	}
}

#endif