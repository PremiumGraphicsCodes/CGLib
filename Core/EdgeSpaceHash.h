#ifndef __CRYSTAL_CORE_EDGE_SPACE_HASH_H__
#define __CRYSTAL_CORE_EDGE_SPACE_HASH_H__

#include "ISpaceHash.h"
#include "Edge.h"

namespace Crystal {
	namespace Core {

class EdgeSpaceHash : public ISpaceHash
{
public:
	EdgeSpaceHash(const float divideLength, const int tableSize);

	void add(Edge* edge);

	std::list<Edge*> getNeighbor(const Math::Vector3d<float>& pos);

	std::list<Edge*> getNeighbor(const Math::Index3d index);

	bool isEmpty() const { return table.empty(); }

private:
	std::vector< std::list<Edge*> > table;

};

	}
}

#endif