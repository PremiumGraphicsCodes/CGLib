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
