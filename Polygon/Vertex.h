#ifndef __CRYSTAL_POLYGON_POLYGON_REDUCTION_H__
#define __CRYSTAL_POLYGON_POLYGON_REDUCTION_H__

#include "../Math/Vector3d.h"
#include "../Util/UnCopyable.h"
#include <list>
#include <array>

namespace Crystal {
	namespace Polygon {

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



class TriangleMesh : private UnCopyable
{
public:
	~TriangleMesh();

	bool hasVertex(Vertex* v);

	void clear();

	Vertex* createVertex(const Math::Vector3d<float>& position);

	TriangleFace* createFace(Vertex* v1, Vertex* v2, Vertex* v3);

	std::vector<Vertex*> getVertices() const { return vertices; }

	TriangleMesh* clone() {
		auto newMesh = new TriangleMesh;
		newMesh->vertices = this->vertices;
		newMesh->faces = this->faces;
		this->vertices.clear();
		this->faces.clear();
	}

private:

	std::vector<Vertex*> vertices;
	std::list<TriangleFace*> faces;
};

	}
}
#endif
