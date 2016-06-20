#ifndef __CRYSTAL_CORE_NODE_GRID_H__
#define __CRYSTAL_CORE_NODE_GRID_H__

#include "../Util/Array2d.h"

namespace Crystal {
	namespace Core {
		class Node;

class TriangleCell
{
public:
	TriangleCell(const std::array<Node*, 3>& nodes) :
		nodes(nodes)
	{}

	std::array<Node*, 3> get() const { return nodes; }

private:
	std::array<Node*, 3> nodes;
};

class QuadCell
{
public:
	QuadCell(const std::array<Node*, 4>& nodes) :
		nodes(nodes)
	{}

	std::array<TriangleCell, 2> toTriangleCells() const {
		TriangleCell c1({ nodes[0], nodes[1], nodes[2] });
		TriangleCell c2({ nodes[2], nodes[3], nodes[0] });
		return{ c1, c2 };
	}
private:
	std::array<Node*, 4> nodes;
};

class INodeGrid
{
public:
	INodeGrid(const int uSize, const int vSize) :
		grid(uSize, vSize)
	{}

	void set(const int u, const int v, Node* n) {
		grid.set(u, v, n);
	}

	Node* get(const int u, const int v) { return grid.get(u, v); }

	virtual Node* getNextU(const int u, const int v) const = 0;

	virtual Node* getPrevU(const int u, const int v) const = 0;

	virtual Node* getNextV(const int u, const int v) const = 0;

	virtual Node* getPrevV(const int u, const int v) const = 0;

	virtual std::vector<QuadCell> toQuadCells() const = 0;

protected:
	Array2d<Node*> grid;

};

class NodeGrid : public INodeGrid
{
public:
	NodeGrid(const int uSize, const int vSize) :
		INodeGrid(uSize, vSize)
	{}

	virtual Node* getNextU(const int u, const int v) const override;

	virtual Node* getPrevU(const int u, const int v) const override;

	virtual Node* getNextV(const int u, const int v) const override;

	virtual Node* getPrevV(const int u, const int v) const override;

	std::vector<QuadCell> toQuadCells() const override;
};

class NodeGrid1d : public INodeGrid
{
public:
	NodeGrid1d(const int uSize, const int vSize) :
		INodeGrid(uSize, vSize)
	{}

	virtual Node* getNextU(const int u, const int v) const override;

	virtual Node* getPrevU(const int u, const int v) const override;

	virtual Node* getNextV(const int u, const int v) const override;

	virtual Node* getPrevV(const int u, const int v) const override;

	std::vector<QuadCell> toQuadCells() const override;
};

class NodeGrid2d : public INodeGrid
{
public:
	NodeGrid2d(const int uSize, const int vSize) :
		INodeGrid(uSize, vSize)
	{}

	virtual Node* getNextU(const int u, const int v) const override;

	virtual Node* getPrevU(const int u, const int v) const override;

	virtual Node* getNextV(const int u, const int v) const override;

	virtual Node* getPrevV(const int u, const int v) const override;

	std::vector<QuadCell> toQuadCells() const override;

};


	}
}

#endif