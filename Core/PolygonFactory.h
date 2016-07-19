#ifndef __CRYSTAL_CORE_POLYGON_FACTORY_H__
#define __CRYSTAL_CORE_POLYGON_FACTORY_H__

#include "../Util/UnCopyable.h"
#include "PolygonMesh.h"
#include "Face.h"

namespace Crystal {
	namespace Core {
		class Volume;
		class ParticleObject;

class PolygonFactory : private UnCopyable
{
public:
	PolygonFactory();

	//PolygonFactory(NodeCollection& nodes, FaceCollection& faces);

	~PolygonFactory();

	void clear();

	void add(const VertexCollection& vs) { this->vertices = vs; }

	void add(PolygonMesh* p);

	PolygonMesh* create(const Math::Curve3d<float>& curve);

	PolygonMesh* create(const Math::CircularCurve3d<float>& curve);

	PolygonMesh* create(const Math::TriangleCurve3d<float>& curve);

	PolygonMesh* create(const Volume& volume, float isolevel);

	PolygonMesh* create(const ParticleObject& particle, const float isolevel, const int levelOfDetail, const Math::Space3d<float>& space);

	void renumber();

	void cleaning();

	void splitByCenter(PolygonMesh* polygon, Face* f);

	void splitByBottom(PolygonMesh* polygon, Face* f);

	void splitByNode(PolygonMesh* polygon, Face* f);

	void addVertex(Face* f, const Math::Point3d<float>& point);

	PolygonMesh* create(std::list<Vertex*>& vertices, std::list<Face*>& faces);

	PolygonMesh* create(VertexCollection& vertices, FaceCollection& faces);

	void createFaces(const std::vector<Vertex*>& vertices);

	std::list<PolygonMesh*> getPolygons() { return polygons; }

	VertexCollection getVertices() const { return vertices; }

	FaceCollection getFaces() const { return faces; }

	PolygonMesh* findPolygonById(const int id);

	PolygonMesh* find(Face* f);

	void merge(PolygonFactory& rhs);

	void remove(PolygonMesh* p);

	void remove(Face* f);

	//PolygonMesh* find(Face* f);

	void simplify(PolygonMesh* p, int howMany);

private:
	VertexCollection vertices;
	FaceCollection faces;
	std::list<PolygonMesh*> polygons;
	int nextId;
};

	}
}

#endif