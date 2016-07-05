#ifndef __CRYSTAL_CORE_SURFACE_H__
#define __CRYSTAL_CORE_SURFACE_H__

//#include "../Math/Curve2d.h"
#include "../Math/Curve3d.h"
#include "../Math/CircularCurve3d.h"
#include "../Math/TriangleCurve3d.h"
#include "Edge.h"
#include "Node.h"
#include "Face.h"
#include "NodeCollection.h"
#include "EdgeCollection.h"
#include "FaceCollection.h"

#include <list>
//#include "Node.h"

namespace Crystal {
	namespace Core {
		class Face;
		class Edge;
		class Node;

		class Surface;


class Surface
{
public:
	Surface();

	Surface(const std::list<Node*>& nodes, const std::list<Edge*>& edges, const std::list<Face*>& faces, const int id);

	~Surface();

	void add(const std::list<Node*>& nodes);

	void add(const std::list<Edge*>& edges);
	
	void add(const std::list<Face*>& faces);

	void merge(Surface& rhs);

	void clear();

	std::list<Face*> getFaces() const { return faces; }

	std::list<Edge*> getEdges() const { return edges; }

	std::list<Node*> getNodes() const { return nodes; }

	std::vector<unsigned int> toIndices() const;

	std::vector<unsigned int> toFaceIds() const;
	
	int getId() const { return id; }

	void move(const Math::Vector3d<float>& v);

	void rotate(const Math::Quaternion<float>& q);

	Math::Vector3d<float> getCenter() const;

	Math::Box3d<float> getBoundingBox() const;

	Math::Sphere<float> getBoundingSphere() const;

	std::vector<Math::Vector3d<float>> getIntersections(const Math::Ray3d<float>& ray) const;

	void scale(const Math::Vector3d<float>& s);

	Node* findNodeById(const int id);

	Face* findFaceById(const int id);

	Edge* findEdgeById(const int id);

	std::list<Node*> getNeighbor(Node* center, const float radius);

	bool has(const Node* node) const;

	bool has(const Edge* edge) const;

	bool has(const Face* face) const;

private:
	int id;
	std::list<Face*> faces;
	std::list<Edge*> edges;
	std::list<Node*> nodes;
};

	}
}

#endif
