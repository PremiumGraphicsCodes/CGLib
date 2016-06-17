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
	if (u == 0) {
		return nullptr;
	}
	return grid.get(u - 1, v);
}

Node* NodeGrid::getNextV(const int u, const int v) const
{
	if (v == (grid.getSizeY() - 1)) {
		return nullptr;
	}
	return grid.get(u, v + 1);
}

Node* NodeGrid::getPrevV(const int u, const int v) const
{
	if (v == 0) {
		return nullptr;
	}
	return grid.get(u, v - 1);
}
