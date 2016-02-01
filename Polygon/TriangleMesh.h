#ifndef __CRYSTAL_POLYGON_TRIANGLE_MESH_H__
#define __CRYSTAL_POLYGON_TRIABGLE_MESH_H__

#include "../Util/UnCopyable.h"
#include "../Math/Vector3d.h"
#include "../Math/Triangle.h"

#include <list>

namespace Crystal {
	namespace Polygon {

		class Vertex;
		class TriangleFace;

class TriangleMesh : private UnCopyable
{
public:
	TriangleMesh() :
		nextIndexId(0)
	{}

	~TriangleMesh();

	bool hasVertex(Vertex* v);

	void clear();

	void sortVertices();

	void add(const Math::Triangle<float>& triangle);

	Vertex* createVertex(const Math::Vector3d<float>& position);

	//void addVertex(Vertex* v) { this->vertices.push_back(v); }

	TriangleFace* createFace(Vertex* v1, Vertex* v2, Vertex* v3);

	std::list<Vertex*> getVertices() const { return vertices; }

	std::vector<TriangleFace*> getFaces() const { return faces; }

	TriangleMesh* clone() {
		auto newMesh = new TriangleMesh;
		newMesh->vertices = this->vertices;
		newMesh->faces = this->faces;
		this->vertices.clear();
		this->faces.clear();
		return newMesh;
	}

private:
	unsigned int nextIndexId;
	std::list<Vertex*> vertices;
	std::vector<TriangleFace*> faces;
};

	}
}

#endif