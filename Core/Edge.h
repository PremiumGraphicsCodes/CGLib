#ifndef __CRYSTAL_CORE_EDGE_H__
#define __CRYSTAL_CORE_EDGE_H__

#include "../Util/UnCopyable.h"
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Core {

class Vertex;
class Face;

class Edge
{
public:
	Edge(Vertex* start, Vertex* end, int id);

	int getId() const { return id; }

	Math::Vector3d<float> getVector() const;

	float getLength() const;

	Vertex* getStart() const { return start; }

	Vertex* getEnd() const { return end; }

	void changeStart(Vertex* n) { this->start = n; }

	void changeEnd(Vertex* n) { this->end = n; }

	Math::Point3d<float> getMidPoint() const;

	Math::Line3d<float> toLine() const;

	void setId(const int id) { this->id = id; }

	Edge* createReverse(const int id) const;

	bool isReverse(const Edge& rhs) const;

	void move(const Math::Vector3d<float>& v);

	bool isShared(const Edge& rhs) const;

	bool isSame(const Edge& rhs) const;

	void connect(Edge* next) {
		next->prev = this;
		this->next = next;
	}

	Edge* getNext() const { return next; }

	Edge* getPrev() const { return prev; }

	bool isCollapsed() const;

	void setFace(Face* f) { this->face = f; }

	Face* getFace() { return face; }

	bool isIsolated() const;

private:
	Edge* prev;
	Edge* next;

	Vertex* start;
	Vertex* end;
	Face* face;
	int id;
};
	}
}

#endif