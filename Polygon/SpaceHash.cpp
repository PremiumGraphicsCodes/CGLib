#include "SpaceHash.h"

#include "../Math/Vector3d.h"
#include "ParticleObject.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

namespace {
	const int p1 = 73856093;
	const int p2 = 19349663;
	const int p3 = 83492791;
	const int hashTableSize = 10000;
}

SpaceHash::SpaceHash(const float divideLength) :
	divideLength(divideLength),
	table(hashTableSize)
{
}


Index3d SpaceHash::toIndex(const Vector3d<float>& pos)
{
	const int ix = static_cast<int>(::fabs(pos.getX()) / divideLength);
	const int iy = static_cast<int>(::fabs(pos.getY()) / divideLength);
	const int iz = static_cast<int>(::fabs(pos.getZ()) / divideLength);
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
			for (auto z = index.getZ() - 1; z <= index.getZ()+1; ++z) {
				auto& ns = getNeighbor(Index3d{ x,y,z });
				neighbors.splice(neighbors.end(), ns);
			}
		}
	}
	std::list<Particle*> results;
	for (auto n : neighbors) {
		if (n->getPosition().getDistanceSquared(pos) < divideLength*divideLength) {
			results.push_back(n);
		}
	}

	return results;
}

std::list<Particle*> SpaceHash::getNeighbor(const Index3d index)
{
	std::list<Particle*> neighbors;
	auto hash = toHash(index);
	auto ps = table[hash];
	for (auto n : ps) {
		neighbors.push_back(n);
	}
	return neighbors;
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

int SpaceHash::toHash(const Index3d& index)
{
	const int x = static_cast<int>( ::fabs(index.getX()) * p1 );
	const int y = static_cast<int>( ::fabs(index.getY()) * p2 );
	const int z = static_cast<int>( ::fabs(index.getZ()) * p3 );
	return (x^y^z) % hashTableSize;
}