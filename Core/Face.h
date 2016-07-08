#ifndef __CRYSTAL_CORE_FACE_H__
#define __CRYSTAL_CORE_FACE_H__

#include <vector>
#include "stdafx.h"

namespace Crystal {
	namespace Core {

class Edge;

class Face : private UnCopyable
{
public:
	//Face() = default;

	Face(const std::vector<Edge*>& edges, int id) :
		edges(edges),
		id( id)
	{}

	float getArea() const;

	Math::Vector3d<float> getNormal() const;

	std::vector<Edge*> getEdges() const { return edges; }

	Math::Vector3d<float> getCenter() const;

	Math::Point3d<float> getCenterPoint() const;

	Math::Triangle3d<float> toTriangle() const;

	bool hasIntersection(const Math::Ray3d<float>& ray) const;

	Math::Vector3d<float> getIntersection(const Math::Ray3d<float>& ray) const;

	void setId(const int id) { this->id = id; }

	int getId() const { return id; }

	std::vector<unsigned int> getNodeIds() const;

	bool has(Edge* e) const;

	bool isConnected() const;

private:
	std::vector<Edge*> edges;
	int id;
};
	}
}

#endif