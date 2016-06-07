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

	Node(const Math::Vector3d<float>& position, const Math::Vector3d<float>& normal, const int id) :
		id(id),
		position(position),
		normal(normal)
	{
	}


	Math::Vector3d<float> getPosition() const { return position; }

	Math::Vector3d<float> getNormal() const { return normal; }

	int getId() const { return id; }

private:
	Math::Vector3d<float> position;
	Math::Vector3d<float> normal;
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