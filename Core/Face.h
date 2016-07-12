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
	Face(Vertex* v1, Vertex* v2, Vertex* v3);

	Vertex* find(Vertex* v);

	void replace(Vertex* oldVertex, Vertex* newVertex);

	Vertex* getV1() const { return vertices[0]; }

	Vertex* getV2() const { return vertices[1]; }

	Vertex* getV3() const { return vertices[2]; }

	Math::Point3d<float> getCenterPoint() const;

	Math::Vector3d<float> getNormal() const;

	std::array< Edge, 3 > toEdges() const;

	bool has(Vertex* v) const;

	float getArea() const;

private:
	std::array< Vertex*, 3> vertices;
};

class FaceCollection
{
public:
	FaceCollection();

	FaceCollection(const std::vector<Face*>& faces);

	~FaceCollection();

	void merge(FaceCollection& rhs);

	Face* create(Vertex* v1, Vertex* v2, Vertex* v3);

	void clear();

	using iterator = std::vector<Face*>::iterator;
	using const_iterator = std::vector<Face*>::const_iterator;

	iterator begin() { return faces.begin(); }

	const_iterator begin() const { return faces.begin(); }

	iterator end() { return faces.end(); }

	const_iterator end() const { return faces.end(); }

	size_t size() const { return faces.size(); }

	Face* operator[](const int i) const { return faces[i]; }

private:
	std::vector<Face*> faces;

};
	}
}

#endif