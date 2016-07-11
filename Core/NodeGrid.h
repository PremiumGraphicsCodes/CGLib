#ifndef __CRYSTAL_CORE_NODE_GRID_H__
#define __CRYSTAL_CORE_NODE_GRID_H__

#include "../Util/Array2d.h"
#include "Vertex.h"
#include "TriangleCell.h"

namespace Crystal {
	namespace Core {
		class Vertex;

class INodeGrid
{
public:
	INodeGrid(const int uSize, const int vSize) :
		grid(uSize, vSize)
	{}

	void set(const int u, const int v, Vertex* n) {
		grid.set(u, v, n);
	}

	Vertex* get(const int u, const int v) { return grid.get(u, v); }

	virtual Vertex* getNextU(const int u, const int v) const = 0;

	virtual Vertex* getPrevU(const int u, const int v) const = 0;

	virtual Vertex* getNextV(const int u, const int v) const = 0;

	virtual Vertex* getPrevV(const int u, const int v) const = 0;

	virtual std::vector<QuadCell> toQuadCells() const = 0;

protected:
	Array2d<Vertex*> grid;

};

class NodeGrid : public INodeGrid
{
public:
	NodeGrid(const int uSize, const int vSize) :
		INodeGrid(uSize, vSize)
	{}

	virtual Vertex* getNextU(const int u, const int v) const override;

	virtual Vertex* getPrevU(const int u, const int v) const override;

	virtual Vertex* getNextV(const int u, const int v) const override;

	virtual Vertex* getPrevV(const int u, const int v) const override;

	std::vector<QuadCell> toQuadCells() const override;
};

class NodeGrid1d : public INodeGrid
{
public:
	NodeGrid1d(const int uSize, const int vSize) :
		INodeGrid(uSize, vSize)
	{}

	virtual Vertex* getNextU(const int u, const int v) const override;

	virtual Vertex* getPrevU(const int u, const int v) const override;

	virtual Vertex* getNextV(const int u, const int v) const override;

	virtual Vertex* getPrevV(const int u, const int v) const override;

	std::vector<QuadCell> toQuadCells() const override;
};

class NodeGrid2d : public INodeGrid
{
public:
	NodeGrid2d(const int uSize, const int vSize) :
		INodeGrid(uSize, vSize)
	{}

	virtual Vertex* getNextU(const int u, const int v) const override;

	virtual Vertex* getPrevU(const int u, const int v) const override;

	virtual Vertex* getNextV(const int u, const int v) const override;

	virtual Vertex* getPrevV(const int u, const int v) const override;

	std::vector<QuadCell> toQuadCells() const override;

};


	}
}

#endif