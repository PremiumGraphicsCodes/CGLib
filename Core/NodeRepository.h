#ifndef __CRYSTAL_CORE_NODE_REPOSITORY_H__
#define __CRYSTAL_CORE_NODE_REPOSITORY_H__

#include "Node.h"
#include "vector"

namespace Crystal {
	namespace Core {

class NodeRepository
{
public:
	NodeRepository();

	NodeRepository(const std::vector<Vertex*>& vertices);

	NodeRepository(const std::list<Vertex*>& vertices);

	~NodeRepository();

	void merge(NodeRepository& rhs);

	void clear();

	using iterator = std::list<Node*>::iterator;
	using const_iterator = std::list<Node*>::const_iterator;

	iterator begin() { return nodes.begin(); }

	const_iterator begin() const { return nodes.begin(); }

	iterator end() { return nodes.end(); }

	const_iterator end() const { return nodes.end(); }

	size_t size() const { return nodes.size(); }

	std::list<Node*> get() { return nodes; }

	void add(Node* v);

	void remove(Node* v);

private:
	std::list<Node*> nodes;
	unsigned int nextId;
};

	}
}

#endif