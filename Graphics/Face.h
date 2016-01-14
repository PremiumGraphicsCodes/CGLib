#ifndef __CRYSTAL_GRAPHICS_FACE_H__
#define __CRYSTAL_GRAPHICS_FACE_H__

#include "HalfEdge.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class Face final
{
public:
	Face()
	{}

	explicit Face(const std::list<HalfEdge<T>>& edges) {
		set(edges);
	}

	void add(const HalfEdge<T>& e) {
		edges.push_back(e);
	}

	void set(const std::list<HalfEdge<T>>& edges) {
		this->edges = edges;
	}

	bool isLine() const { return edges.size() == 1; }

	std::list<HalfEdge<T>> getEdges() const { return edges; }

	Math::Vector3d<T> getNormal() const { return edges.front().getStartVertex().getNormal(); }

private:
	std::list<HalfEdge<T>> edges;
};

	}
}

#endif