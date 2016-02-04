#ifndef __CRYSTAL_POLYGON_POLYGON_OBJECT_H__
#define __CRYSTAL_POLYGON_POLYGON_OBJECT_H__

#include "../Util/UnCopyable.h"
#include "../Math/Vector3d.h"
#include "../Math/Triangle.h"
#include "Vertex.h"
#include "Face.h"

#include <list>

namespace Crystal {
	namespace Polygon {

class Vertex;
class Face;


class PolygonObject : private UnCopyable
{
public:
	PolygonObject() :
		nextIndexId(0)
	{}

	~PolygonObject();


	void add(const Math::Triangle<float>& triangle);

	VectorId* createPosition(const Math::Vector3d<float>& position);

	VectorId* createNormal(const Math::Vector3d<float>& normal);

	VectorId* createTexCoord(const Math::Vector3d<float>& texCoord);

	Vertex* createVertex(VectorId* position, VectorId* normal = nullptr, VectorId* texCoord = nullptr);

	Vertex* createVertexFromIndices(const int positionIndex, const int normalIndex, const int texIndex);

	//void addVertex(Vertex* v) { this->vertices.push_back(v); }

	Face* createFace(Vertex* v1, Vertex* v2, Vertex* v3);

	Face* createFace(const int v1, const int v2, const int v3);

	std::list< Face* > createFaces(const std::vector<int>& ids);

	std::list< Face* > createFaces(const std::vector<Vertex*>& vertices);

	VertexCollection getVertices() const { return vertices; }

	VectorIdCollection getPositions() const{ return positions; }

	VectorIdCollection getNormals() const { return positions; }

	VectorIdCollection getTexCoords() const { return texCoords; }

	FaceCollection getFaces() const { return faces; }

	void clear();

private:
	unsigned int nextIndexId;
	VertexCollection vertices;
	VectorIdCollection positions;
	VectorIdCollection normals;
	VectorIdCollection texCoords;
	FaceCollection faces;
};

	}
}

#endif