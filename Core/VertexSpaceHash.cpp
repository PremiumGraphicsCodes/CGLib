#include "stdafx.h"
#include "VertexSpaceHash.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

VertexSpaceHash::VertexSpaceHash(const float divideLength, const int hashTableSize) :
	ISpaceHash(divideLength, hashTableSize),
	table(hashTableSize)
{
}

void VertexSpaceHash::add(Vertex* v)
{
	const auto hashIndex = toHash(v->getPosition());
	table[hashIndex].push_back(v);
}

void VertexSpaceHash::remove(Vertex* v)
{
	const auto hashIndex = toHash(v->getPosition());
	table[hashIndex].remove(v);
}

std::list<Vertex*> VertexSpaceHash::getNeighbor(Vertex* object)
{
	return getNeighbor(object->getPosition());
}


std::list<Vertex*> VertexSpaceHash::getNeighbor(const Vector3d<float>& pos)
{
	std::list<Vertex*> neighbors;
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

	std::list<Vertex*> results;
	for (auto n : neighbors) {
		//if (n->getPosition().getDistanceSquared(pos) < length*length) {
		if (n->getPosition().getDistanceSquared(pos) < divideLength * divideLength) {
			results.push_back(n);
		}
	}

	return results;
}

std::list<Vertex*> VertexSpaceHash::getNeighbor(const Vector3d<float>& pos, const float length)
{
	std::list<Vertex*> neighbors;
	Index3d index = toIndex(pos);
	for (auto x = index.getX() - 1; x <= index.getX() + 1; ++x) {
		for (auto y = index.getY() - 1; y <= index.getY() + 1; ++y) {
			for (auto z = index.getZ() - 1; z <= index.getZ() + 1; ++z) {
				const auto& ns = table[toHash(Index3d{ x,y,z })];
				for (const auto& n : ns) {
					const auto distanceSquared = n->getPosition().getDistanceSquared(pos);
					if (distanceSquared < length*length) {
						//if (n->getPosition().getDistanceSquared(pos) < divideLength * divideLength) {
						neighbors.emplace_back(n);
					}
				}

				//neighbors.insert(neighbors.end(), ns.begin(), ns.end());
			}
		}
	}
	neighbors.sort();
	neighbors.unique();

	return std::move(neighbors);
}

std::list<Vertex*> VertexSpaceHash::getNeighbor(const Index3d index)
{
	auto hash = toHash(index);
	return table[hash];
}

std::list<Vertex*> VertexSpaceHash::findSameStrictly(const Vector3d<float>& pos)
{
	const auto hashIndex = toHash(pos);
	auto neighbors = table[hashIndex];
	std::list<Vertex*> results;
	for (auto n : neighbors) {
		if (n->getPosition() == pos) {
			results.push_back(n);
		}
	}
	return results;
}
