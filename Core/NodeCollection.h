#ifndef __CRYSTAL_CORE_NODE_COLLECTION_H__
#define __CRYSTAL_CORE_NODE_COLLECTION_H__

#include "../Util/UnCopyable.h"
#include <list>
#include "Node.h"

namespace Crystal {
	namespace Core {

class NodeCollection : private UnCopyable
{
public:
	NodeCollection();

	~NodeCollection();

	Node* create(const Math::Point3d<float>& p);

	void clear();

	std::list<Node*> get() const { return nodes; }

	void merge(NodeCollection& rhs);

	void remove(Node* n);

	Node* findById(const int id) const;

private:
	std::list<Node*> nodes;

	int nextId;

};
	}
}

#endif