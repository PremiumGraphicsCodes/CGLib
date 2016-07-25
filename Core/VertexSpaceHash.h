#ifndef __CRYSTAL_CORE_VERTEX_SPACE_HASH_H__
#define __CRYSTAL_CORE_VERTEX_SPACE_HASH_H__

#include "ISpaceHash.h"
#include "Vertex.h"

namespace Crystal {
	namespace Core {

class VertexSpaceHash : public ISpaceHash
{
public:
	VertexSpaceHash(const float divideLength, const int tableSize);

	void add(Vertex* particle);

	std::list<Vertex*> getNeighbor(Vertex* object);

	std::list<Vertex*> getNeighbor(const Math::Vector3d<float>& pos, const float length);

	std::list<Vertex*> getNeighbor(const Math::Vector3d<float>& pos);

	std::list<Vertex*> getNeighbor(const Math::Index3d index);

	std::list<Vertex*> findSameStrictly(const Math::Vector3d<float>& pos);

	bool isEmpty() const { return table.empty(); }

private:
	std::vector< std::list<Vertex*> > table;

};

	}
}

#endif