#ifndef __CRYSTAL_CORE_SURFACE_H__
#define __CRYSTAL_CORE_SURFACE_H__

//#include "../Math/Curve2d.h"
#include "../Math/Curve3d.h"
#include "../Math/CircularCurve3d.h"

#include <list>
//#include "Node.h"

namespace Crystal {
	namespace Core {
		class Face;
		class Edge;
		class Node;

class Surface
{
public:
	Surface();

	//explicit Surface(const Math::Curve2d<float>& curve):

	Surface(const Math::Curve3d<float>& curve, const int id = -1);

	~Surface();

	void add(const Math::Curve3d<float>& curve);

	void add(const Math::CircularCurve3d<float>& curve);

	void clear();

	std::list<Face*> getFaces() const { return faces; }

	std::list<Edge*> getEdges() const { return edges; }

	std::list<Node*> getNodes() const { return nodes; }

	std::vector<unsigned int> toIndices() const;

	Face* subdiv(const Face* face);
	
	int getId() const { return id; }

	void move(const Math::Vector3d<float>& v);

	void rotate(const Math::Quaternion<float>& q);

	Math::Vector3d<float> getCenter() const;

	Math::Box3d<float> getBoundingBox() const;

	Math::Sphere<float> getBoundingSphere() const;

	std::vector<Math::Vector3d<float>> getIntersections(const Math::Ray3d<float>& ray) const;

private:
	int id;
	int nextNodeId;
	int nextEdgeId;
	int nextFaceId;
	std::list<Face*> faces;
	std::list<Edge*> edges;
	std::list<Node*> nodes;
};

	}
}

#endif
