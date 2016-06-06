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

private:
	Node* start;
	Node* end;
	const int id;
};
	}
}

#endif