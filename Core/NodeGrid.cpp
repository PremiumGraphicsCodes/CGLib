#include "stdafx.h"
#include "NodeGrid.h"

using namespace Crystal::Core;

Node* NodeGrid::getNextU(const int u, const int v) const
{
	if (v == (grid.getSizeY()-1)) {
		return nullptr;
	}
	return grid.get(u , v+1);
}

Node* NodeGrid::getPrevU(const int u, const int v) const
{
	if (v == 0) {
		return nullptr;
	}
	return grid.get(u, v-1);
}

Node* NodeGrid::getNextV(const int u, const int v) const
{
	if (u == (grid.getSizeX() - 1)) {
		return nullptr;
	}
	return grid.get(u+1, v);
}

Node* NodeGrid::getPrevV(const int u, const int v) const
{
	if (v == 0) {
		return nullptr;
	}
	return grid.get(u-1, v);
}

std::vector<QuadCell> NodeGrid::toQuadCells() const
{
	std::vector<QuadCell> cells;
	for (int u = 0; u < grid.getSizeX()-1; ++u) {
		for (int v = 0; v < grid.getSizeY()-1; ++v) {
			std::array< Node*, 4 > c;
			c[0] = grid.get(u, v);
			c[1] = grid.get(u + 1, v);
			c[2] = grid.get(u + 1, v+1);
			c[3] = grid.get(u, v + 1);
			cells.push_back(c);
		}
	}
	return cells;
}



Node* NodeGrid1d::getNextU(const int u, const int v) const
{
	if (v == (grid.getSizeY() - 1)) {
		return grid.get(u,0);
	}
	return grid.get(u, v + 1);
}

Node* NodeGrid1d::getPrevU(const int u, const int v) const
{
	if (v == 0) {
		return grid.get(u,grid.getSizeY()-1);
	}
	return grid.get(u, v - 1);
}

Node* NodeGrid1d::getNextV(const int u, const int v) const
{
	if (u == (grid.getSizeX() - 1)) {
		return nullptr;
	}
	return grid.get(u + 1, v);
}

Node* NodeGrid1d::getPrevV(const int u, const int v) const
{
	if (v == 0) {
		return nullptr;
	}
	return grid.get(u - 1, v);
}

std::vector<QuadCell> NodeGrid1d::toQuadCells() const
{
	std::vector<QuadCell> cells;
	for (int u = 0; u < grid.getSizeX()-1; ++u) {
		for (int v = 0; v < grid.getSizeY()-1; ++v) {
			std::array< Node*, 4 > c;
			c[0] = grid.get(u, v);
			c[1] = grid.get(u + 1, v);
			c[2] = grid.get(u + 1, v + 1);
			c[3] = grid.get(u, v + 1);
			cells.push_back(c);
		}
	}
	/*
	{
		const int u = grid.getSizeX()-1;
		for (int v = 0; v < grid.getSizeY() - 1; ++v) {
			std::array< Node*, 4 > c;
			c[0] = grid.get(u, v);
			c[1] = grid.get(0, v);
			c[2] = grid.get(0, v + 1);
			c[3] = grid.get(u, v + 1);
			cells.push_back(c);
		}
	}
	*/
	return cells;
}


Node* NodeGrid2d::getNextU(const int u, const int v) const
{
	if (v == (grid.getSizeY() - 1)) {
		return grid.get(u, 0);
	}
	return grid.get(u, v + 1);
}

Node* NodeGrid2d::getPrevU(const int u, const int v) const
{
	if (v == 0) {
		return grid.get(u, grid.getSizeY() - 1);
	}
	return grid.get(u, v - 1);
}

Node* NodeGrid2d::getNextV(const int u, const int v) const
{
	if (u == (grid.getSizeX() - 1)) {
		return grid.get(0,v);
	}
	return grid.get(u + 1, v);
}

Node* NodeGrid2d::getPrevV(const int u, const int v) const
{
	if (v == 0) {
		return grid.get(grid.getSizeX() - 1, v);
	}
	return grid.get(u - 1, v);
}

std::vector<QuadCell> NodeGrid2d::toQuadCells() const
{
	std::vector<QuadCell> cells;
	for (int u = 0; u < grid.getSizeX() - 1; ++u) {
		for (int v = 0; v < grid.getSizeY() - 1; ++v) {
			std::array< Node*, 4 > c;
			c[0] = grid.get(u, v);
			c[1] = grid.get(u + 1, v);
			c[2] = grid.get(u + 1, v + 1);
			c[3] = grid.get(u, v + 1);
			cells.push_back(c);
		}
	}
	{
		const int u = grid.getSizeX() - 1;
		for (int v = 0; v < grid.getSizeY() - 1; ++v) {
			std::array< Node*, 4 > c;
			c[0] = grid.get(u, v);
			c[1] = grid.get(0, v);
			c[2] = grid.get(0, v + 1);
			c[3] = grid.get(u, v + 1);
			cells.push_back(c);
		}
	}
	{
		const int v = grid.getSizeY() - 1;
		for (int u = 0; u < grid.getSizeY() - 1; ++u) {
			std::array< Node*, 4 > c;
			c[0] = grid.get(u, v);
			c[1] = grid.get(u, 0);
			c[2] = grid.get(u+1, 0);
			c[3] = grid.get(u, v);
			cells.push_back(c);
		}
	}

	return cells;
}
