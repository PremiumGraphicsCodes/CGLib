#ifndef __CRYSTAL_GRAPHICS_POLYGON_REDUCTION_H__
#define __CRYSTAL_GRAPHICS_POLYGON_REDUCTION_H__

#include "../Math/Vector3d.h"
#include <list>
#include <array>
#include <memory>

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

private:
	std::list<TriangleFace*> faces;

	Math::Vector3d<float> position;
};

class Edge
{
public:
	Edge(std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2) : v1(v1), v2(v2)
	{}

	float getLength() const;

	std::shared_ptr<Vertex> getV1() const { return v1; }

	std::shared_ptr<Vertex> getV2() const { return v2; }

private:
	std::shared_ptr<Vertex> v1;
	std::shared_ptr<Vertex> v2;
};

class TriangleFace
{
public:
	TriangleFace(std::array<std::shared_ptr<Vertex>, 3> vertices) :
		vertices(vertices)
	{
		for (auto v : vertices) {
			v->addFace(this);
		}
	}

	std::array<std::shared_ptr<Vertex>, 3> getVertices() const { return vertices; }

	bool hasVertex(const std::shared_ptr<Vertex>& v);

	Math::Vector3d<float> getNormal() { return normal; }

	void replaceVertex(std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2);

private:
	std::array<std::shared_ptr<Vertex>, 3> vertices;

	Math::Vector3d<float> normal;
};

class TriangleMesh
{
public:
	~TriangleMesh();

	void clear();

	void removeOverlappedVerticies();

	void reduceTo(const int desired);

	std::shared_ptr<Vertex> createVertex(const Math::Vector3d<float>& position);

	std::shared_ptr<TriangleFace> createFace(const std::array< std::shared_ptr<Vertex>, 3>& vertices);

	std::list<std::shared_ptr< Vertex> > getVertices() const { return vertices; }

	/*
		vertices.push_back( )
		return
		new Vertex(); }
		*/

private:

	std::list<std::shared_ptr<Vertex>> vertices;
	std::list<std::shared_ptr<Edge>> edges;
	std::list<std::shared_ptr<TriangleFace>> faces;
};

		}
	}
}
#endif
