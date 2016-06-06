#ifndef __CRYSTAL_CORE_NODE_H__
#define __CYRSTAL_CORE_NODE_H__

#include "../Math/Vector3d.h"
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Core {
		class Edge;
		
class Node : private UnCopyable
{
public:
	/*
	Node(const int id) :
		id(id)
	{}
	*/

	Node(const Math::Vector3d<float>& position, const int id):
		id(id),
		position(position)
	{
	}

	Math::Vector3d<float> getPosition() const { return position; }

	int getId() const { return id; }

private:
	Math::Vector3d<float> position;
	const int id;
};

class NodeGrid2d
{
public:
	NodeGrid2d(const int uNum, const int vNum);

	void set(const int u, const int v, Node* node) {
		grid[u][v] = node;
	}

	Node* get(const int u, const int v) {
		return grid[u][v];
	}

private:
	std::vector< std::vector<Node*> > grid;
};
	}
}

#endif