#ifndef __CRYSTAL_GRAPHICS_LINE_ID_BUFFER_H__
#define __CRYSTAL_GRAPHICS_LINE_ID_BUFFER_H__

#include "Buffer3d.h"
#include "Buffer1d.h"
#include "Buffer4d.h"

#include "../Math/Point3d.h"
#include "../Math/Line3d.h"
#include "../Core/PolygonMesh.h"
#include "../Graphics/ColorRGBA.h"
#include "DrawableID.h"

namespace Crystal {
	namespace Graphics {

class LineIdBlock
{
public:
	LineIdBlock(const std::vector<unsigned int>& indices, const DrawableID& did) :
		indices(indices)
	{
		idColor.add(did.toColor());
	}

	std::vector<unsigned int> indices;
	Buffer4d<float> idColor;
};


class LineIdBuffer
{
public:
	LineIdBuffer() = default;

	LineIdBuffer(const Core::PolygonFactory& factory, const unsigned char groupId);

	void add(const Core::PolygonMesh& surface, const unsigned char groupId);

	void add(const Core::PolygonMesh& surface, const DrawableID& did);

	void add(const Math::Line3d<float>& line, const DrawableID& did);

	void add(const Math::Polyline3d<float>& polyline, const DrawableID& did);

	void add(const Core::PolygonMesh& polygon);

	Graphics::Buffer3d<float> getPosition() const { return position; }

	Buffer4d<float> getIds() const { return idColors; }

	std::vector<unsigned int> getIndices() const { return ids; }

private:
	Buffer3d<float> position;
	Buffer4d<float> idColors;
	std::vector<unsigned int> ids;
};

	}
}

#endif