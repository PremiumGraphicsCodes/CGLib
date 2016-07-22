#include "stdafx.h"
#include "EdgeSpaceHash.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

EdgeSpaceHash::EdgeSpaceHash(const float divideLength, const int hashTableSize) :
	ISpaceHash(divideLength, hashTableSize),
	table(hashTableSize)
{
}

void EdgeSpaceHash::add(Edge* edge)
{
	auto curve = edge->getCurve();
	auto positions = curve.toPositionsByLength(divideLength);
	for (auto p : positions) {
		const auto hashIndex = toHash(p);
		table[hashIndex].push_back(edge);
	}
}

std::list<Edge*> EdgeSpaceHash::getNeighbor(const Vector3d<float>& pos)
{
	std::list<Edge*> neighbors;
	Index3d index = toIndex(pos);
	for (auto x = index.getX() - 1; x <= index.getX() + 1; ++x) {
		for (auto y = index.getY() - 1; y <= index.getY() + 1; ++y) {
			for (auto z = index.getZ() - 1; z <= index.getZ() + 1; ++z) {
				auto& ns = table[toHash(Index3d{ x,y,z })];
				neighbors.insert(neighbors.end(), ns.begin(), ns.end());
			}
		}
	}
	neighbors.sort();
	neighbors.unique();

	return neighbors;
}

std::list<Edge*> EdgeSpaceHash::getNeighbor(const Index3d index)
{
	auto hash = toHash(index);
	return table[hash];
}