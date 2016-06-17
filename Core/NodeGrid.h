#ifndef __CRYSTAL_CORE_NODE_GRID_H__
#define __CRYSTAL_CORE_NODE_GRID_H__

#include "../Util/Array2d.h"
#include "Node.h"

namespace Crystal {
	namespace Core {

class INodeGrid
{

};

class NodeGrid
{
public:
	NodeGrid(const int uSize, const int vSize) :
		grid(uSize, vSize)
	{
	}

	void set(const int u, const int v, Node* n) {
		grid.set(u, v, n);
	}

	Node* getNextU(const int u, const int v) const;

	Node* getPrevU(const int u, const int v) const;

	Node* getNextV(const int u, const int v) const;

	Node* getPrevV(const int u, const int v) const;

private:
	Array2d<Node*> grid;
};
	}
}

#endif