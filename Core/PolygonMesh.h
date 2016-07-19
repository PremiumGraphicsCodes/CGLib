#ifndef __CRYSTAL_POLYGON_POLYGON_MESH_H__
#define __CRYSTAL_POLYGON_POLYGON_MESH_H__

#include "../Util/UnCopyable.h"
#include "Vertex.h"
#include "Face.h"
#include "VertexCollection.h"
#include "FaceCollection.h"

#include <list>

namespace Crystal {
	namespace Core {

class Vertex;
class Face;

class PolygonMesh : private UnCopyable
{
public:
	PolygonMesh(const unsigned int id = -1) :
		id(id)
	{}

	PolygonMesh(const std::list<Vertex*>& vertices, const std::list<Face*>& faces, const unsigned int id = -1);

	~PolygonMesh();

	void setId(const int id) { this->id = id; }

	unsigned int getId() const { return id; }

	void removeOverlappedVertices();

	VertexCollection getVertices() const { return vertices; }

	void transform(const Math::Matrix4d<float>& matrix);

	//std::vector<Math::Vector3d<float>> getTexCoords() const { return texCoords; }

	std::list<Face*> getFaces() const { return faces; }

	std::vector<int> toIndices() const;

	void clear();

	void smooth(Vertex* v);

	void simplify(const Edge& e);

	void cleaning();

	void add(Face* f);

	void add(Vertex* v);

	bool has(Face* f);

	void remove(Face* f);

	PolygonMesh* clone(const int id);

	Edge* getShortestEdge();

	//std::list<Vertex*> getNeighbors(Vertex* v, const float length);

private:
	unsigned int id;
	std::list<Vertex*> vertices;
	std::list<Face*> faces;
};

	}
}

#endif