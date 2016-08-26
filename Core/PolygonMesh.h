#ifndef __CRYSTAL_POLYGON_POLYGON_MESH_H__
#define __CRYSTAL_POLYGON_POLYGON_MESH_H__

#include "../Util/UnCopyable.h"
#include "Vertex.h"
#include "Face.h"

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

	std::list<HalfEdge*> getEdges() const;

	void clear();

	void smooth(const float angle);

	void smooth(Vertex* v);

	void simplify(const HalfEdge& e);

	void add(Face* f);

	bool has(Face* f);

	bool has(HalfEdge* e);

	bool has(Vertex* v);

	void remove(Face* f);

	PolygonMesh* clone(const int id);

	HalfEdge* getShortestEdge();

	void mergeDouble(PolygonMesh* rhs, float distance);

	Math::Vector3d<float> getCenter() const;

	void move(const Math::Vector3d<float>& v);

	void scale(const Math::Vector3d<float>& s);

	void rotate(const Math::Quaternion<float>& quaternion);

	void merge(PolygonMesh& rhs);

	void reverse();

	std::list<Vertex*> findInnerVertices();

	std::list<Vertex*> findBoundaryVertices();

	std::list<HalfEdge*> findBoundaryEdges();

	void updateNormals();
		
private:
	unsigned int id;
	std::list<Face*> faces;
};

	}
}

#endif