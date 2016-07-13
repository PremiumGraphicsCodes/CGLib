#ifndef __CRYSTAL_CORE_POLYGON_FACTORY_H__
#define __CRYSTAL_CORE_POLYGON_FACTORY_H__

#include "../Util/UnCopyable.h"
#include "PolygonMesh.h"
#include "Face.h"

namespace Crystal {
	namespace Core {

class PolygonFactory : private UnCopyable
{
public:
	PolygonFactory();

	//PolygonFactory(NodeCollection& nodes, FaceCollection& faces);

	~PolygonFactory();

	void add(const VertexCollection& vs) { this->vertices = vs; }

	void add(const Math::Curve3d<float>& curve);

	void add(const Math::CircularCurve3d<float>& curve);

	void add(const Math::TriangleCurve3d<float>& curve);

	void renumber();

	void cleaning();

	void splitByCenter(PolygonMesh* polygon, Face* f);

	void splitByBottom(PolygonMesh* polygon, Face* f);

	void splitByNode(PolygonMesh* polygon, Face* f);

	PolygonMesh* create(const int id);

	void createFaces(const std::vector<Vertex*>& vertices);

private:
	VertexCollection vertices;
	FaceCollection faces;

};

	}
}

#endif