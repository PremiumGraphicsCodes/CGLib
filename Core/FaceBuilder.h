#ifndef __CRYSTAL_CORE_FACE_BUILDER_H__
#define __CRYSTAL_CORE_FACE_BUILDER_H__

#include "EdgeCollection.h"
#include "FaceCollection.h"

namespace Crystal {
	namespace Core {

class FaceBuilder
{
public:
	FaceBuilder(const std::vector<Vertex*>& vertices);

	~FaceBuilder();

	Face* build(int i1, int i2, int i3);

	void clear();

private:
	std::vector<Vertex*> vertices;
	EdgeCollection edges;
	FaceCollection faces;
};

	}
}

#endif