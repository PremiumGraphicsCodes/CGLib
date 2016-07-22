#ifndef __CRYSTAL_CORE_FACE_BUILDER_H__
#define __CRYSTAL_CORE_FACE_BUILDER_H__

#include "EdgeCollection.h"
#include "FaceCollection.h"

namespace Crystal {
	namespace Core {

class FaceBuilder
{
public:
	FaceBuilder(const std::vector<Vertex*>& vertices) :
		vertices(vertices)
	{}

	Face* build(int i1, int i2, int i3) {
		auto e1 = edges.create(vertices[i1], vertices[i2]);
		auto e2 = edges.create(vertices[i2], vertices[i3]);
		auto e3 = edges.create(vertices[i3], vertices[i1]);
		return faces.create(e1, e2, e3);
	}

	~FaceBuilder() {
		clear();
	}

	void clear() {
		edges.clear();
		faces.clear();
	}

private:
	std::vector<Vertex*> vertices;
	EdgeCollection edges;
	FaceCollection faces;
};

	}
}

#endif