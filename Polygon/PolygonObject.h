#ifndef __CRYSTAL_POLYGON_POLYGON_OBJECT_H__
#define __CRYSTAL_POLYGON_POLYGON_OBJECT_H__

#include "../Util/UnCopyable.h"
#include "../Math/Vector3d.h"
#include "../Math/Triangle.h"
#include "Vertex.h"

#include <list>

namespace Crystal {
	namespace Polygon {

class Vertex;
class TriangleFace;


class PolygonObject : private UnCopyable
{
public:
	PolygonObject() :
		nextIndexId(0)
	{}

	~PolygonObject();

	bool hasVertex(Vertex* v);

	void clear();

	void sortVertices();

	void add(const Math::Triangle<float>& triangle);

	VectorId* createPosition(const Math::Vector3d<float>& position);

	VectorId* createNormal(const Math::Vector3d<float>& normal);

	VectorId* createTexCoord(const Math::Vector3d<float>& texCoord);

	Vertex* createVertex(VectorId* v, VectorId* normal = nullptr, VectorId* texCoord = nullptr);

	Vertex* createVertexFromIndices(const int positionIndex, const int normalIndex, const int texIndex);

	//void addVertex(Vertex* v) { this->vertices.push_back(v); }

	TriangleFace* createFace(Vertex* v1, Vertex* v2, Vertex* v3);

	TriangleFace* createFace(const int v1, const int v2, const int v3);

	std::list< TriangleFace* > createFaces(const std::vector<int>& ids);

	std::list< TriangleFace* > createFaces(const std::vector<Vertex*>& vertices);

	std::list<Vertex*> getVertices() const { return vertices; }

	VectorIdCollection getPositions() const{ return positions; }

	VectorIdCollection getNormals() const { return positions; }

	VectorIdCollection getTexCoords() const { return texCoords; }

	std::vector<TriangleFace*> getFaces() const { return faces; }

	PolygonObject* clone() {
		auto newMesh = new PolygonObject;
		newMesh->vertices = this->vertices;
		newMesh->positions = this->positions;
		newMesh->normals = this->normals;
		newMesh->texCoords = this->texCoords;
		newMesh->faces = this->faces;
		this->vertices.clear();
		this->positions.clear();
		this->normals.clear();
		this->texCoords.clear();
		this->faces.clear();
		return newMesh;
	}

private:
	unsigned int nextIndexId;
	std::list<Vertex*> vertices;
	VectorIdCollection positions;
	VectorIdCollection normals;
	VectorIdCollection texCoords;
	std::vector<TriangleFace*> faces;
};

	}
}

#endif