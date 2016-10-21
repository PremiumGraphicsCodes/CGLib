#ifndef __CRYSTAL_PHYSICS_IISPH_SPACE_HASH_H__
#define __CRYSTAL_POLYGON_IISPH_SPACE__HASH_H__

#include "../Core/ISpaceHash.h"
#include <vector>
#include <list>

namespace Crystal {
	namespace Physics {

class IISPHParticle;

template<typename T = IISPHParticle>
class IISPHSpaceHash : public ISpaceHash
{
public:
	IISPHSpaceHash(const float divideLength, const int tableSize);

	void add(T* particle);

	std::list<T*> getNeighbor(T* object);

	std::list<T*> getNeighbor(const Math::Vector3d<float>& pos, const float length);

	std::list<T*> getNeighbor(const Math::Vector3d<float>& pos);

	std::list<T*> getNeighbor(const Math::Index3d index);

	bool isEmpty() const { return table.empty(); }

private:
	std::vector< std::list<T*> > table;
};


	}
}

#endif