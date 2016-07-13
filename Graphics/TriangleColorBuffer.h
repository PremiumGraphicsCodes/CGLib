#ifndef __CRYSTAL_GRAPHICS_TRIANGLE_COLOR_BUFFER_H__
#define __CRYSTAL_GRAPHICS_TRIANGLE_COLOR_BUFFER_H__

#include <vector>

#include "Buffer3d.h"
#include "Buffer4d.h"

#include "DrawableID.h"

namespace Crystal {
	namespace Core {
		class PolygonMesh;
		class Vertex;
	}
	namespace Graphics {

		class TriangleColorBuffer
		{
		public:
			TriangleColorBuffer();

			void add(const Core::PolygonMesh& polygon, const ColorRGBA<float>& color);

			void add(const Math::Point3d<float>& point, const ColorRGBA<float>& did);

			void clear();

			Buffer3d<float> getPositions() const { return positions; }

			Buffer4d<float> getColors() const { return colors; }

			std::vector<unsigned int> getIndices() const { return indices; }

		private:
			std::vector<unsigned int> indices;
			Buffer3d<float> positions;
			Buffer4d<float> colors;
			int nextId;
		};

	}
}

#endif