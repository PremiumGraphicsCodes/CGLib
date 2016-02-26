#ifndef __CRYSTAL_IO_OBJ_VERTEX_H__
#define __CRYSTAL_IO_OBJ_VERTEX_H__

namespace Crystal {
	namespace IO {

struct OBJVertex
{
	OBJVertex() :
		positionIndex(-1),
		normalIndex(-1),
		texIndex(-1)
	{}


	OBJVertex(const int positionIndex, const int normalIndex = -1, const int texIndex = -1) :
		positionIndex(positionIndex),
		normalIndex(normalIndex),
		texIndex(texIndex)
	{}

	bool hasNormal() const {
		return this->normalIndex != -1;
	}

	bool hasTex() const {
		return this->texIndex != -1;
	}

	int positionIndex;
	int normalIndex;
	int texIndex;

	bool operator==(const OBJVertex& rhs) const {
		return
			this->positionIndex == rhs.positionIndex &&
			this->normalIndex == rhs.normalIndex &&
			this->texIndex == rhs.texIndex;
	}
};

	}
}

#endif