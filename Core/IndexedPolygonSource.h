#ifndef __CRYSTAL_CORE_INDEXED_POLYGON_SOURCE_H__
#define __CRYSTAL_CORE_INDEXED_POLYGON_SOURCE_H__

#include "stdafx.h"

namespace Crystal {
	namespace Core {
		class PolygonMesh;

class IndexedVertex
{
public:
	IndexedVertex() :
		positionIndex(-1),
		normalIndex(-1),
		texCoordIndex(-1)
	{}

	explicit IndexedVertex(const int positionIndex) :
		positionIndex(positionIndex),
		normalIndex(-1),
		texCoordIndex(-1)
	{}

	IndexedVertex(const int positionIndex, const int normalIndex) :
		positionIndex(positionIndex),
		normalIndex(normalIndex),
		texCoordIndex(-1)
	{}

	int positionIndex;
	int normalIndex;
	int texCoordIndex;
};

class IndexedFace
{
public:
	std::vector<IndexedVertex> vertices;
};

class IndexedPolygonSource
{
public:
	IndexedPolygonSource(
		const std::vector<Math::Vector3d<float>>& positions,
		const std::vector<Math::Vector3d<float>>& normals,
		const std::vector<Math::Vector2d<float>>& texCoords);

	void build(const std::vector<IndexedFace>& faces);

	PolygonMesh* get() { return polygon; }

private:
	std::vector<Math::Vector3d<float>> positions;
	std::vector<Math::Vector3d<float>> normals;
	std::vector<Math::Vector2d<float>> texCoords;
	PolygonMesh* polygon;
};
	}
}

#endif