#include "stdafx.h"
#include "FaceSpaceHash.h"
#include "Vertex.h"
#include "HalfEdge.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

FaceSpaceHash::FaceSpaceHash(const float divideLength, const int hashTableSize) :
	ISpaceHash(divideLength, hashTableSize),
	table(hashTableSize)
{
}

void FaceSpaceHash::add(Face* face)
{
	const auto& bb = face->toTriangle().getBoundingBox();
	const auto& points = bb.toPoints(divideLength);
	for (auto p : points) {
		const auto hashIndex = toHash(p);
		table[hashIndex].push_back(face);
	}
}

std::list<Face*> FaceSpaceHash::getNeighbor(const Vector3d<float>& pos)
{
	Index3d index = toIndex(pos);
	return table[toHash(index)];
}

std::list<Face*> FaceSpaceHash::getNeighbor(const Index3d index)
{
	auto hash = toHash(index);
	return table[hash];
}