#ifndef __CRYSTAL_GRAPHICS_HALF_EDGE_H__
#define __CRYSTAL_GRAPHICS_HALF_EDGE_H__

#include <list>

#include "Vertex.h"

namespace Crystal {
	namespace Graphics {

template<typename T>
class HalfEdge
{
public:
	
	HalfEdge(const Vertex<T>& start, const Vertex<T>& end) :
		start( start ),
		end( end )
	{}

	HalfEdge* getPrev() const { return prev; }

	void setPrev(const HalfEdge prev) { this->prev = &prev; }

	HalfEdge* getNext() const { return next; }

	void setNext(const HalfEdge next) { this->next = &next; }

	Vertex<T> getStartVertex() const { return start; }

	Vertex<T> getEndVertex() const { return end; }

	Math::Vector3d<T> getStartPosition() const { return start.getPosition(); }

	Math::Vector3d<T> getEndPosition() const { return end.getPosition(); }

	bool isStart() const { return getPrev() == nullptr; }

	bool isEnd() const { return getNext() == nullptr; }

	bool isValid() const { return start != nullptr || end != nullptr; }

	bool isIsolated() const { return (getPrev() == this) && (getNext() == this); }

	static std::list< HalfEdge > createOpen(const std::vector<Vertex<T>>& vertices) {
		if (vertices.size() < 2) {
			return std::list< HalfEdge >();
		}
		std::list< HalfEdge > edges;
		for (size_t i = 0; i < vertices.size() - 1; ++i) {
			edges.emplace_back(HalfEdge(vertices[i], vertices[i + 1]));
		}
		return std::move(edges);
	}

	static std::list< HalfEdge > createClosed(const std::vector<Vertex<T>>& vertices) {
		if (vertices.size() < 2) {
			return std::list< HalfEdge >();
		}
		std::list< HalfEdge > edges = createOpen(vertices);
		const Vertex<T>& v1 = vertices.front();
		const Vertex<T>& v2 = vertices.back();
		edges.emplace_back(HalfEdge(v2, v1));
		return std::move(edges);
	}



private:
	Vertex<T> start;
	Vertex<T> end;

	HalfEdge* prev;
	HalfEdge* next;
};

	}
}

#endif