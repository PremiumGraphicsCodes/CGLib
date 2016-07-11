#ifndef __CRYSTAL_CORE_FACE_H__
#define __CRYSTAL_CORE_FACE_H__

#include <vector>
#include "stdafx.h"

namespace Crystal {
	namespace Core {

class Edge;
class Surface;

class Face : private UnCopyable
{
public:
	//Face() = default;

	Face(const std::array<Edge*, 3>& edges, int id);

	float getArea() const;

	bool isCCW() const;

	bool isCW() const;

	Math::Vector3d<float> getNormal() const;

	std::array<Edge*, 3> getEdges() const { return edges; }

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

	bool isCollapsed() const;

	bool isDegenerated() const;

	void setSurface(Surface *s) { this->surface = s; }

	Surface* getSurface() { return surface; }

private:
	std::array<Edge*, 3> edges;
	Surface* surface;
	int id;
};
	}
}

#endif