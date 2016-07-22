#ifndef __CRYSTAL_POLYGON_SPACE_HASH_H__
#define __CRYSTAL_POLYGON_SPACE_HASH_H__

#include "ISpaceHash.h"
#include "Vertex.h"
#include <vector>
#include <list>

namespace Crystal {
	namespace Core {

class Particle;
class ParticleObject;


class SpaceHash : public ISpaceHash
{
public:
	SpaceHash(const float divideLength, const int tableSize);

	void add(Particle* particle);

	std::list<Particle*> getNeighbor(Particle* object);

	std::list<Particle*> getNeighbor(const Math::Vector3d<float>& pos, const float length);

	std::list<Particle*> getNeighbor(const Math::Vector3d<float>& pos);

	std::list<Particle*> getNeighbor(const Math::Index3d index);

	bool isEmpty() const { return table.empty(); }

private:
	std::vector< std::list<Particle*> > table;

};


	}
}

#endif