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
	namespace Core {
		class PolygonMesh;
		class Actor;
		class Surface;
		class Edge;
	}
	namespace Graphics {

class LineIdBuffer
{
public:
	void clear();

	void add(const Core::Surface& surface, const DrawableID& did);

	void add(const Math::Line3d<float>& line, const DrawableID& did);

	void add(const Math::Polyline3d<float>& polyline, const DrawableID& did);

	Graphics::Buffer3d<float> getPosition() const { return position; }

	Buffer4d<float> getIdColors() const { return idColors; }

	std::vector<unsigned int> getIndices() const { return ids; }

private:
	Buffer3d<float> position;
	Buffer4d<float> idColors;
	std::vector<unsigned int> ids;
};

	}
}

#endif