#ifndef __CRYSTAL_IO_OBJ_FACE_H__
#define __CRYSTAL_IO_OBJ_FACE_H__

#include <vector>
#include "OBJVertex.h"

namespace Crystal {
	namespace IO {

struct OBJFace
{
	OBJFace()
	{}

	OBJFace(const std::vector<OBJVertex>& vertices) :
		vertices(vertices)
	{}

	bool operator==(const OBJFace& rhs) const {
		return vertices == rhs.vertices;
	}

	std::vector<OBJVertex> getVertices() const { return vertices; }

	std::string usemtlname;

private:
	std::vector<OBJVertex> vertices;
};


	}
}

#endif