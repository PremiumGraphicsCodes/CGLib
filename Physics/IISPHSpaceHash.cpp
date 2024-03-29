#include "IISPHSpaceHash.h"

#include "IISPHParticle.h"
#include "PBSPHParticle.h"

using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Physics;

template<typename T>
IISPHSpaceHash<T>::IISPHSpaceHash(const float divideLength, const int hashTableSize) :
	ISpaceHash(divideLength, hashTableSize),
	table(hashTableSize)
{
}

template<typename T>
std::list<T*> IISPHSpaceHash<T>::getNeighbor(T* object)
{
	return getNeighbor(object->getPosition());
}

template<typename T>
std::list<T*> IISPHSpaceHash<T>::getNeighbor(const Vector3d<float>& pos)
{
	std::list<T*> neighbors;
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

	std::list<T*> results;
	for (auto n : neighbors) {
		//if (n->getPosition().getDistanceSquared(pos) < length*length) {
		if (n->getPosition().getDistanceSquared(pos) < divideLength * divideLength) {
			results.push_back(n);
		}
	}

	return results;
}

template<typename T>
std::list<T*> IISPHSpaceHash<T>::getNeighbor(const Vector3d<float>& pos, const float length)
{
	std::list<T*> neighbors;
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

template<typename T>
std::list<T*> IISPHSpaceHash<T>::getNeighbor(const Index3d index)
{
	auto hash = toHash(index);
	return table[hash];
}

template<typename T>
void IISPHSpaceHash<T>::add(T* particle)
{
	const auto hashIndex = toHash(particle->getPosition());
	table[hashIndex].push_back(particle);
}

template class IISPHSpaceHash<IISPHParticle>;
template class IISPHSpaceHash<PBSPHParticle>;