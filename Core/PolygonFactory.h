#ifndef __CRYSTAL_CORE_POLYGON_FACTORY_H__
#define __CRYSTAL_CORE_POLYGON_FACTORY_H__

#include "../Util/UnCopyable.h"
#include "NodeCollection.h"
#include "Face.h"

namespace Crystal {
	namespace Core {
		class PolygonMesh;

class PolygonFactory : private UnCopyable
{
public:
	PolygonFactory() = default;

	PolygonFactory(NodeCollection& nodes, FaceCollection& faces);

	~PolygonFactory();

	void clear();

	PolygonMesh* create(const Math::Curve3d<float>& curve, const int id = -1);

	PolygonMesh* create(const Math::CircularCurve3d<float>& curve, const int id = -1);

	PolygonMesh* create(const Math::TriangleCurve3d<float>& curve, const int id = -1);

	void merge(PolygonFactory& rhs);

	void remove(Face* f);

	void remove(Vertex* n);

	PolygonMesh* findSurfaceById(const int id);

	Vertex* findNodeById(const int id) const;

	Face* findFaceById(const int id) const;

	std::list<PolygonMesh*> getPolygons() const { return polygons; }

	//std::list<TriFace*> getFaces() { return faces.get(); }

	void renumber();

	void cleaning();


private:
	PolygonMesh* create(int id, const std::vector<Vertex*>& nodes, const std::vector<Face*>& faces);

	NodeCollection nodes;
	FaceCollection faces;
	std::list<PolygonMesh*> polygons;
};

	}
}

#endif