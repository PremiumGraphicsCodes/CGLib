#ifndef __CRYSTAL_CORE_FACE_BUILDER_H__
#define __CRYSTAL_CORE_FACE_BUILDER_H__

#include "HalfEdgeCollection.h"
#include "FaceCollection.h"

namespace Crystal {
	namespace Core {

class FaceBuilder
{
public:
	FaceBuilder(const std::vector<Vertex*>& vertices);

	~FaceBuilder();

	Face* build(int i1, int i2, int i3);

	HalfEdgeCollection getEdge() { return edges; }

	void clear();

private:
	std::vector<Vertex*> vertices;
	HalfEdgeCollection edges;
	FaceCollection faces;
};

	}
}

#endif