#ifndef __CRYSTAL_CORE_POLYGON_FACTORY_H__
#define __CRYSTAL_CORE_POLYGON_FACTORY_H__

#include "../Util/UnCopyable.h"
#include "PolygonMesh.h"
#include "Face.h"
#include "EdgeCollection.h"
#include <map>

namespace Crystal {
	namespace Core {
		class Volume;
		class ParticleObject;
		class PolygonBuilder;

class PolygonFactory : private UnCopyable
{
public:
	PolygonFactory();

	PolygonFactory(VertexCollection& vertices);

	~PolygonFactory();

	void clear();

	void add(const VertexCollection& vs) { this->vertices = vs; }

	void add(PolygonMesh* p);

	void renumber();

	void cleaning();

	void splitByCenter(PolygonMesh* polygon, Face* f);

	void splitByBottom(PolygonMesh* polygon, Face* f);

	void splitByNode(PolygonMesh* polygon, Face* f);

	void addVertex(Face* f, const Math::Point3d<float>& point);

	PolygonMesh* create(PolygonBuilder& builder);

	PolygonMesh* create(FaceCollection& faces);

	std::list<PolygonMesh*> getPolygons() const { return polygons; }

	VertexCollection getVertices() const { return vertices; }

	EdgeCollection getEdges() const { return edges; }

	FaceCollection getFaces() const { return faces; }

	PolygonMesh* findPolygonById(const int id);

	PolygonMesh* find(Face* f);

	PolygonMesh* find(Vertex* v);

	PolygonMesh* find(HalfEdge* e);

	void merge(PolygonFactory& rhs);

	void remove(PolygonMesh* p);

	void remove(Face* f);

	void destory(Vertex* v);

	void destory(HalfEdge* e);

	void destory(Face* f);

	void destory(PolygonMesh* p);

	//PolygonMesh* find(Face* f);

	void simplify(PolygonMesh* p, int howMany);

	Face* createFace(Vertex* v1, Vertex* v2, Vertex* v3);

	HalfEdge* getShared(HalfEdge* e);

	std::list<HalfEdge*> findDouble(PolygonMesh* lhs, PolygonMesh* rhs, float distance);

	std::list<Vertex*> findIsolatedVertices();

	void divide(PolygonMesh* polygon,const float area);

private:
	VertexCollection vertices;
	EdgeCollection edges;
	FaceCollection faces;
	std::list<PolygonMesh*> polygons;
	int nextId;
};

	}
}

#endif