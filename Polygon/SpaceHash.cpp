#include "SpaceHash.h"

#include "../Math/Vector3d.h"
#include "ParticleObject.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;


SpaceHash::SpaceHash(const float divideLength, const int hashTableSize) :
	divideLength(divideLength),
	table(hashTableSize)
{
}


Index3d SpaceHash::toIndex(const Vector3d<float>& pos)
{
	const int ix = (pos.getX() + 10.0f) / divideLength;
	const int iy = (pos.getY() + 10.0f) / divideLength;
	const int iz = (pos.getZ() + 10.0f) / divideLength;
	return{ ix, iy, iz };
}

std::vector<Particle*> SpaceHash::getNeighbor(Particle* object)
{
	return getNeighbor(object->getPosition());
}

std::vector<Particle*> SpaceHash::getNeighbor(const Vector3d<float>& pos)
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

	std::vector<Particle*> results;
	for (auto n : neighbors) {
		if (n->getPosition().getDistanceSquared(pos) < n->getRadius()*n->getRadius()) {
			results.push_back(n);
		}
	}

	return results;
}

std::vector<Particle*> SpaceHash::getNeighbor(const Index3d index)
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