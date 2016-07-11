#ifndef __CRYSTAL_CORE_NODE_COLLECTION_H__
#define __CRYSTAL_CORE_NODE_COLLECTION_H__

#include "../Util/UnCopyable.h"
#include <list>
#include "Vertex.h"

namespace Crystal {
	namespace Core {

class NodeCollection : private UnCopyable
{
public:
	NodeCollection();

	~NodeCollection();

	Vertex* create(const Math::Point3d<float>& p);

	void clear();

	std::list<Vertex*> get() const { return nodes; }

	void merge(NodeCollection& rhs);

	void remove(Vertex* n);

	Vertex* findById(const int id) const;

	void renumber();

	void cleaning();

private:
	std::list<Vertex*> nodes;

	int nextId;

};
	}
}

#endif