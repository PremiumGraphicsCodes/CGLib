#ifndef __CRYSTAL_POLYGON_SPACE_HASH_H__
#define __CRYSTAL_POLYGON_SPACE_HASH_H__

#include <vector>
#include <list>
#include "../Math/Index3d.h"
#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Polygon {

class Particle;
class ParticleObject;

class SpaceHash
{
public:
	SpaceHash(const float divideLength);

	void add(Particle* particle);

	std::list<Particle*> getNeighbor(Particle* object);

private:
	std::vector< std::list<Particle*> > table;

	int toHash(const Math::Vector3d<float>& pos);

	int toHash(const Math::Index3d& index);

	Math::Index3d toIndex(const Math::Vector3d<float>& pos);

	const float divideLength;
};
	}
}

#endif