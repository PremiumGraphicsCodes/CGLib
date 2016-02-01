#ifndef __CRYSTAL_GRAPHICS_SURFACE_H__
#define __CRYSTAL_GRAPHICS_SURFACE_H__

#include <vector>

#include "../Util/UnCopyable.h"

#include "../Math/Vector3d.h"
#include "../Math/Triangle.h"
#include "../Math/Volume3d.h"
#include "../Math/Box.h"
#include "Vertex.h"
#include "Face.h"
#include "Material.h"
#include "ColorRGBA.h"
#include "HalfEdge.h"

namespace Crystal {
	namespace Graphics {
		class Material;

template<typename T>
class Surface final  {
public:

	Surface() = default;

	~Surface() = default;

	void clear() {
		vertices.clear();
		edges.clear();
		faces.clear();
	}

	std::list<HalfEdge<T>> getEdges() const { return edges; }

	std::vector<Vertex<T>> getVertices() const { return vertices; }

	std::list<Face<T>> getFaces() const { return faces; }

	void add(const Math::Triangle<T>& t);

	void add(const Math::Box<T>& box);

	void move(const Math::Vector3d<T>& vector) {
		for (auto& v : vertices) {
			v.move(vector);
		}
	}

private:
	std::vector<Vertex<T>> vertices;
	std::list<HalfEdge<T>> edges;
	std::list<Face<T>> faces;
};

	}
}

#endif