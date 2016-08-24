#ifndef __CRYSTAL_CORE_POLYGON_REPOSITORY_H__
#define __CRYSTAL_CORE_POLYGON_REPOSITORY_H__

#include "../Util/UnCopyable.h"
#include "PolygonMesh.h"
#include "Face.h"
#include "Edge.h"
#include "HalfEdgeRepository.h"
#include "FaceRepository.h"
#include <map>

namespace Crystal {
	namespace Core {
		class Edge;
		class Volume;
		class ParticleObject;
		class PolygonBuilder;

class PolygonRepository : private UnCopyable
{
public:
	PolygonRepository();

	PolygonRepository(VertexCollection& vertices);

	~PolygonRepository();

	void clear();

	void add(const VertexCollection& vs) { this->vertices = vs; }

	void add(PolygonMesh* p);

	void renumber();

	void cleaning();

	void splitByCenter(PolygonMesh* polygon, Face* f);

	void split(PolygonMesh* polygon, Edge& e);

	Vertex* split(PolygonMesh* polygon, HalfEdge* e);

	void split(PolygonMesh* polygon, Face* f);

	void addVertex(Face* f, const Math::Point3d<float>& point);

	PolygonMesh* create(PolygonBuilder& builder);

	PolygonMesh* create(FaceRepository& faces);

	std::list<PolygonMesh*> getPolygons() const { return polygons; }

	VertexCollection getVertices() const { return vertices; }

	HalfEdgeRepository getEdges() const { return edges; }

	FaceRepository getFaces() const { return faces; }

	PolygonMesh* findPolygonById(const int id);

	PolygonMesh* find(Face* f);

	PolygonMesh* find(Vertex* v);

	PolygonMesh* find(HalfEdge* e);

	void merge(PolygonRepository& rhs);

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
	HalfEdgeRepository edges;
	FaceRepository faces;
	std::list<PolygonMesh*> polygons;
	int nextId;
};

	}
}

#endif