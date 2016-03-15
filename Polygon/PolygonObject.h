#ifndef __CRYSTAL_POLYGON_POLYGON_OBJECT_H__
#define __CRYSTAL_POLYGON_POLYGON_OBJECT_H__

#include "../Util/UnCopyable.h"
#include "../Math/Vector3d.h"
#include "../Math/Triangle.h"
#include "../Math/Quad.h"
#include "Vertex.h"
#include "Face.h"

#include <list>

namespace Crystal {
	namespace Math {
		template<typename>
		class Sphere;
		template<typename>
		class Box;
	}
	namespace Polygon {

class Vertex;
class Face;


class PolygonObject : private UnCopyable
{
public:
	PolygonObject() :
		nextIndexId(0)
	{}

	~PolygonObject();


	void add(const Math::Triangle<float>& triangle);

	void add(const Math::Quad<float>& quad);

	void add(const Math::Box<float>& box);

	void add(const Math::Sphere<float>& sphere, const int udiv, const int vdiv);

	void add(PolygonObject* rhs);

	void removeOverlappedVertices() { vertices.sort(); }

	Vertex* createVertex(Math::Vector3d<float> position, Math::Vector3d<float> normal = Math::Vector3d<float>(), Math::Vector3d<float> texCoord = Math::Vector3d<float>());

	Vertex* findVertexById(const unsigned int id) const;

	//Face* findFaceById(const unsigned int id) const;

	Face* createFace(Vertex* v1, Vertex* v2, Vertex* v3);

	Face* createFace(const int v1, const int v2, const int v3);

	std::list< Face* > createFaces(const std::vector<int>& ids);

	std::list< Face* > createFaces(const std::vector<Vertex*>& vertices);

	VertexCollection getVertices() const { return vertices; }

	std::vector<Math::Vector3d<float>> getPositions() const{
		std::vector<Math::Vector3d<float>> positions;
		for (auto p : vertices) {
			positions.push_back(p->getPosition());
		}
		return positions;
	}

	std::vector<Math::Vector3d<float>> getNormals() const {
		std::vector<Math::Vector3d<float>> positions;
		for (auto p : vertices) {
			positions.push_back(p->getNormal());
		}
		return positions;
	}

	//std::vector<Math::Vector3d<float>> getTexCoords() const { return texCoords; }

	FaceCollection getFaces() const { return faces; }

	void clear();

private:
	unsigned int nextIndexId;
	VertexCollection vertices;
	FaceCollection faces;
};

	}
}

#endif