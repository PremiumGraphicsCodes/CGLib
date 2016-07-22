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
	Index3d index = toIndex(pos);
	return table[toHash(index)];
}

std::list<Edge*> EdgeSpaceHash::getNeighbor(const Index3d index)
{
	auto hash = toHash(index);
	return table[hash];
}