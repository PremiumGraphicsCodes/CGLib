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

	PolygonMesh(const std::list<Face*>& faces, const unsigned int id = -1);

	~PolygonMesh();

	void setId(const int id) { this->id = id; }

	unsigned int getId() const { return id; }

	std::list<Face*> getFaces() const { return faces; }

	std::list<Vertex*> getVertices() const;

	std::list<Edge*> getEdges() const;

	void clear();

	void smooth(Vertex* v);

	void simplify(const Edge& e);

	void add(Face* f);

	bool has(Face* f);

	void remove(Face* f);

	PolygonMesh* clone(const int id);

	Edge* getShortestEdge();

	void mergeDouble(PolygonMesh* rhs, float distance);

	Math::Vector3d<float> getCenter() const;

private:
	unsigned int id;
	std::list<Face*> faces;
};

	}
}

#endif