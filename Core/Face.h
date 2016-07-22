#ifndef __CRYSTAL_POLYGON_FACE_H__
#define __CRYSTAL_POLYGON_FACE_H__

#include "stdafx.h"
#include "Edge.h"
#include <map>

namespace Crystal {
	namespace Core {

		class Vertex;

class Face
{
public:
	Face(Edge* e1, Edge* e2, Edge* e3, const int id = -1);

	Face(const std::array<Edge*,3>& edges, const int id = -1);

	Vertex* find(Vertex* v);

	Vertex* getV1() const { return edges[0]->getStart(); }

	Vertex* getV2() const { return edges[1]->getStart(); }

	Vertex* getV3() const { return edges[2]->getStart(); }

	Math::Point3d<float> getCenterPoint() const;

	Math::Vector3d<float> getNormal() const;

	Math::Orientation getOrientation(const Math::Vector3d<float>& pos) const;

	std::array< Edge*, 3 > getEdges() const;

	std::array< Vertex*, 3 > getVertices() const;

	bool has(Vertex* v) const;

	float getArea() const;

	int getId() const { return id; }

	void changeId(const int id) { this->id = id; }

	bool isDegenerated() const;

	//std::array< Vertex*, 3> getVertexIds() const;

	void toDegenerate();

	std::map<Vertex*, Vertex*> findDouble(const Face& rhs, const float distance);

	void mergeDouble(const Face& rhs, float distance);

	Math::Triangle3d<float> toTriangle() const;

private:
	std::array< Edge*, 3 > edges;
	//std::array< Vertex*, 3> vertices;
	int id;
};

	}
}

#endif