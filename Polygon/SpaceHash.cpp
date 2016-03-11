#include "SpaceHash.h"

#include "../Math/Vector3d.h"
#include "ParticleObject.h"
#include "Particle.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;


SpaceHash::SpaceHash(const float divideLength, const int hashTableSize) :
	divideLength(divideLength),
	table(hashTableSize)
{
}


Index3d SpaceHash::toIndex(const Vector3d<float>& pos)
{
	const int ix = static_cast<int>( (pos.getX() ) / divideLength );
	const int iy = static_cast<int>( (pos.getY() ) / divideLength );
	const int iz = static_cast<int>( (pos.getZ() ) / divideLength );
	return{ ix, iy, iz };
}

std::list<Particle*> SpaceHash::getNeighbor(Particle* object)
{
	return getNeighbor(object->getPosition());
}

std::list<Particle*> SpaceHash::getNeighbor(const Vector3d<float>& pos)
{
	std::list<Particle*> neighbors;
	Index3d index = toIndex(pos);
	for (auto x = index.getX() - 1; x <= index.getX()+1; ++x) {
		for (auto y = index.getY() - 1; y <= index.getY()+1; ++y) {
			for (auto z = index.getZ() - 1; z <= index.getZ() + 1; ++z) {
				auto& ns = table[toHash(Index3d{ x,y,z })];
				neighbors.insert(neighbors.end(), ns.begin(), ns.end());
			}
		}
	}
	neighbors.sort();
	neighbors.unique();

	std::list<Particle*> results;
	for (auto n : neighbors) {
		//if (n->getPosition().getDistanceSquared(pos) < length*length) {
		if(n->getPosition().getDistanceSquared(pos) < divideLength * divideLength) {
			results.push_back(n);
		}
	}

	return results;
}

std::list<Particle*> SpaceHash::getNeighbor(const Vector3d<float>& pos, const float length)
{
	std::list<Particle*> neighbors;
	Index3d index = toIndex(pos);
	for (auto x = index.getX() - 1; x <= index.getX() + 1; ++x) {
		for (auto y = index.getY() - 1; y <= index.getY() + 1; ++y) {
			for (auto z = index.getZ() - 1; z <= index.getZ() + 1; ++z) {
				const auto& ns = table[toHash(Index3d{ x,y,z })];
				for (const auto& n : ns) {
					const auto distanceSquared = n->getPosition().getDistanceSquared(pos);
					if ( distanceSquared < length*length) {
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

std::list<Particle*> SpaceHash::getNeighbor(const Index3d index)
{
	auto hash = toHash(index);
	return table[hash];
}



void SpaceHash::add(Particle* particle)
{
	const auto hashIndex = toHash(particle->getPosition());
	table[hashIndex].push_back(particle);
}


int SpaceHash::toHash(const Vector3d<float>& pos)
{
	return toHash(toIndex(pos));
}

#include <bitset>

int SpaceHash::toHash(const Index3d& index)
{
	std::bitset<32> x = index.getX() * p1;
	std::bitset<32> y = index.getY() * p2;
	std::bitset<32> z = index.getZ() * p3;
	//assert(x >= 0);
	//assert(y >= 0);
	//assert(z >= 0);
	const auto value = (x ^ y ^ z).to_ulong();
	return value % table.size();
}