#ifndef __CRYSTAL_CORE_FACE_SPACE_HASH_H__
#define __CRYSTAL_CORE_FACE_SPACE_HASH_H__

#include "ISpaceHash.h"
#include "Face.h"

namespace Crystal {
	namespace Core {

class FaceSpaceHash : public ISpaceHash
{
public:
	FaceSpaceHash(const float divideLength, const int tableSize);

	void add(Face* edge);

	std::list<Face*> getNeighbor(const Math::Vector3d<float>& pos);

	std::list<Face*> getNeighbor(const Math::Index3d index);

	bool isEmpty() const { return table.empty(); }

private:
	std::vector< std::list<Face*> > table;

};

	}
}

#endif