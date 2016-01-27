#ifndef __CRYSTAL_GRAPHICS_POLYGON_REDUCTION_H__
#define __CRYSTAL_GRAPHICS_POLYGON_REDUCTION_H__

#include "../Math/Vector3d.h"
#include <list>
#include <array>

namespace Crystal {
	namespace Graphics {
		namespace Experiment {

class Vertex;
class TriangleFace;


class Vertex
{
public:
	Vertex(const Math::Vector3d<float>& position) :
		position(position)
	{}

	void addFace(TriangleFace* face) { this->faces.push_back(face); }

	Math::Vector3d<float> getPosition() const { return position; }
				
	std::list< TriangleFace* > getFaces() const { return faces; }

	float computeCost();

	std::list<Vertex*> getNeighbors() const { return neighbors; }

private:
	std::list<TriangleFace*> faces;
	std::list<Vertex*> neighbors;
	Vertex* collapse;
	float cost;

	Math::Vector3d<float> position;
};

class Edge
{
public:
	Edge(Vertex* v1, Vertex* v2) : v1(v1), v2(v2)
	{}

	float computeCost() const;

	float getLength() const;

	void collapse();

	Vertex* getV1() const { return v1; }

	Vertex* getV2() const { return v2; }

private:
	Vertex* v1;
	Vertex* v2;
};

class TriangleFace
{
public:
	TriangleFace(std::array<Vertex*, 3> vertices) :
		vertices(vertices)
	{
		for (auto v : vertices) {
			v->addFace(this);
		}
	}

	bool hasVertex(const Vertex* v);

	Math::Vector3d<float> getNormal() { return normal; }

	void replaceVertex(Vertex* v1, Vertex* v2);

private:
	std::array<Vertex*, 3> vertices;

	Math::Vector3d<float> normal;
};

class TriangleMesh
{
public:
	~TriangleMesh();

	void clear();

	void removeOverlappedVerticies();

	void reduceTo(const int desired);

	Vertex* createVertex(const Math::Vector3d<float>& position);

	TriangleFace* createFace(const std::array< Vertex*, 3>& vertices);

	std::list<Vertex*> getVertices() const { return vertices; }

	/*
		vertices.push_back( )
		return
		new Vertex(); }
		*/

private:
	Edge* getMinimunCostEdge();

	std::list<Vertex*> vertices;
	std::list<Edge*> edges;
	std::list<TriangleFace*> faces;
};

		}
	}
}
#endif
