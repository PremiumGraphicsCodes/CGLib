#include "SpaceHash.h"

#include "../Math/Vector3d.h"
#include "ParticleObject.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

namespace {
	const int p1 = 73856093;
	const int p2 = 19349663;
	const int p3 = 83492791;
}

SpaceHash::SpaceHash(const float divideLength, const int hashTableSize) :
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

std::vector<Particle*> SpaceHash::getNeighbor(Particle* object)
{
	return getNeighbor(object->getPosition());
}

std::vector<Particle*> SpaceHash::getNeighbor(const Vector3d<float>& pos)
{
	std::vector<Particle*> neighbors;
	Index3d index = toIndex(pos);
	for (auto x = index.getX() - 1; x <= index.getX()+1; ++x) {
		for (auto y = index.getY() - 1; y <= index.getY()+1; ++y) {
			for (auto z = index.getZ() - 1; z <= index.getZ()+1; ++z) {
				auto& ns = getNeighbor(Index3d{ x,y,z });
				std::copy(ns.begin(), ns.end(), std::back_inserter(neighbors));
			}
		}
	}
	std::vector<Particle*> results;
	for (auto n : neighbors) {
		if (n->getPosition().getDistanceSquared(pos) < divideLength*divideLength) {
			results.push_back(n);
		}
	}

	return results;
}

std::vector<Particle*> SpaceHash::getNeighbor(const Index3d index)
{
	std::vector<Particle*> neighbors;
	auto hash = toHash(index);
	auto ns = table[hash];
	return ns;
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
	return (x^y^z) % table.size();
}