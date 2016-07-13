#ifndef __CRYSTAL_POLYGON_FACE_H__
#define __CRYSTAL_POLYGON_FACE_H__

#include "stdafx.h"

namespace Crystal {
	namespace Core {

		class Vertex;
		class Edge;

class Face
{
public:
	Face(Vertex* v1, Vertex* v2, Vertex* v3, const int id = -1);

	Vertex* find(Vertex* v);

	void replace(Vertex* oldVertex, Vertex* newVertex);

	Vertex* getV1() const { return vertices[0]; }

	Vertex* getV2() const { return vertices[1]; }

	Vertex* getV3() const { return vertices[2]; }

	Math::Point3d<float> getCenterPoint() const;

	Math::Vector3d<float> getNormal() const;

	Math::Orientation getOrientation(const Math::Vector3d<float>& pos) const;

	std::array< Edge, 3 > toEdges() const;

	bool has(Vertex* v) const;

	float getArea() const;

	int getId() const { return id; }

	void changeId(const int id) { this->id = id; }



	//std::array< Vertex*, 3> getVertexIds() const;

private:
	std::array< Vertex*, 3> vertices;
	int id;
};

	}
}

#endif