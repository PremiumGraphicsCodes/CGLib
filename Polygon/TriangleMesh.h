#ifndef __CRYSTAL_POLYGON_TRIANGLE_MESH_H__
#define __CRYSTAL_POLYGON_TRIANGLE_MESH_H__

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

	Math::Vector3d<float>* createPosition(const Math::Vector3d<float>& position);

	Math::Vector3d<float>* createNormal(const Math::Vector3d<float>& normal);

	Math::Vector3d<float>* createTexCoord(const Math::Vector3d<float>& texCoord);

	Vertex* createVertex(Math::Vector3d<float>* v, Math::Vector3d<float>* normal = nullptr, Math::Vector3d<float>* texCoord = nullptr);

	Vertex* createVertexFromIndices(const int positionIndex, const int normalIndex, const int texIndex);

	//void addVertex(Vertex* v) { this->vertices.push_back(v); }

	TriangleFace* createFace(Vertex* v1, Vertex* v2, Vertex* v3);

	TriangleFace* createFace(const int v1, const int v2, const int v3);

	std::list< TriangleFace* > createFaces(const std::vector<int>& ids);

	std::list< TriangleFace* > createFaces(const std::vector<Vertex*>& vertices);

	std::list<Vertex*> getVertices() const { return vertices; }

	std::vector< Math::Vector3d<float>* > getPositions() const{ return positions; }

	std::vector< Math::Vector3d<float>* > getNormals() const { return positions; }


	std::vector<TriangleFace*> getFaces() const { return faces; }

	TriangleMesh* clone() {
		auto newMesh = new TriangleMesh;
		newMesh->vertices = this->vertices;
		newMesh->positions = this->positions;
		newMesh->normals = this->normals;
		newMesh->texCoords = this->texCoords;
		newMesh->faces = this->faces;
		this->vertices.clear();
		this->positions.clear();
		this->normals.clear();
		this->texCoords.clear();
		this->faces.clear();
		return newMesh;
	}

private:
	unsigned int nextIndexId;
	std::list<Vertex*> vertices;
	std::vector<Math::Vector3d<float>*> positions;
	std::vector<Math::Vector3d<float>*> normals;
	std::vector<Math::Vector3d<float>*> texCoords;
	std::vector<TriangleFace*> faces;
};

	}
}

#endif