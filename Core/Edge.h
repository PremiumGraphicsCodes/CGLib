#ifndef __CRYSTAL_CORE_EDGE_H__
#define __CRYSTAL_CORE_EDGE_H__

#include "../Util/UnCopyable.h"
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Core {

class Node;

class Edge : private UnCopyable
{
public:
	Edge(Node* start, Node* end, int id);

	int getId() const { return id; }

	Math::Vector3d<float> getVector() const;

	float getLength() const;

	Node* getStart() const { return start; }

	Node* getEnd() const { return end; }

	void changeStart(Node* n) { this->start = n; }

	void changeEnd(Node* n) { this->end = n; }

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

private:
	Edge* prev;
	Edge* next;

	Node* start;
	Node* end;
	int id;
};
	}
}

#endif