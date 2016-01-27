#ifndef __CRYSTAL_GRAPHICS_POLYGON_REDUCTION_H__
#define __CRYSTAL_GRAPHICS_POLYGON_REDUCTION_H__

#include "../Math/Vector3d.h"
#include "../Util/UnCopyable.h"
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


	Math::Vector3d<float> getPosition() const { return position; }

private:

	Math::Vector3d<float> position;
};

class TriangleFace
{
public:
	TriangleFace(std::array<Vertex*, 3> vertices) :
		vertices(vertices)
	{
	}

	std::array<Vertex*, 3> getVertices() const { return vertices; }

	Math::Vector3d<float> getNormal() { return normal; }

	void replaceVertex(Vertex* v1, Vertex* v2);

private:
	std::array<Vertex*, 3> vertices;

	Math::Vector3d<float> normal;
};

class TriangleMesh : private UnCopyable
{
public:
	~TriangleMesh();

	bool hasVertex(Vertex* v);

	void clear();

	Vertex* createVertex(const Math::Vector3d<float>& position);

	TriangleFace* createFace(const std::array< Vertex*, 3 > & vertices);

	std::list<Vertex*> getVertices() const { return vertices; }

	TriangleMesh* clone() {
		auto newMesh = new TriangleMesh;
		newMesh->vertices = this->vertices;
		newMesh->faces = this->faces;
		this->vertices.clear();
		this->faces.clear();
	}

private:

	std::list<Vertex*> vertices;
	std::list<TriangleFace*> faces;
};

		}
	}
}
#endif
