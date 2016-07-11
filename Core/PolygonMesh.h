#ifndef __CRYSTAL_POLYGON_POLYGON_OBJECT_H__
#define __CRYSTAL_POLYGON_POLYGON_OBJECT_H__

#include "../Util/UnCopyable.h"
#include "Vertex.h"
#include "TriFace.h"

#include <list>

namespace Crystal {
	namespace Math {
		template<typename>
		class Sphere;
		template<typename>
		class Box3d;
		template<typename>
		class Matrix4d;
	}
	namespace Core {

class Vertex;
class TriFace;


class PolygonMesh : private UnCopyable
{
public:
	PolygonMesh(const unsigned int id = -1) :
		id(id),
		nextIndexId(0)
	{}

	~PolygonMesh();

	unsigned int getId() const { return id; }

	void add(const Math::Triangle3d<float>& triangle);

	void add(const Math::Quad<float>& quad);

	void add(const Math::Box3d<float>& box);

	void add(const Math::Sphere<float>& sphere, const int udiv, const int vdiv);

	//void add(const Math::Ellipsoid<float>& ellipsoid, const int udiv, const int vdiv);

	void add(const Math::Cone<float>& cone, const int div);


	void create(const Math::Curve3d<float>& curve, const int id = -1);

	void create(const Math::CircularCurve3d<float>& curve, const int id = -1);

	void create(const Math::TriangleCurve3d<float>& curve, const int id = -1);


	void merge(PolygonMesh* rhs);

	void removeOverlappedVertices() { vertices.sort(); }

	Vertex* createVertex(Math::Vector3d<float> position, Math::Vector3d<float> normal = Math::Vector3d<float>(), Math::Vector2d<float> texCoord = Math::Vector2d<float>());

	Vertex* findVertexById(const unsigned int id) const;

	//Face* findFaceById(const unsigned int id) const;

	TriFace* createFace(Vertex* v1, Vertex* v2, Vertex* v3);

	TriFace* createFace(const int v1, const int v2, const int v3);

	PolygonMesh* clone(const unsigned int id = -1);

	std::list< TriFace* > createFaces(const std::vector<int>& ids);

	std::list< TriFace* > createFaces(const std::vector<Vertex*>& vertices);

	VertexCollection getVertices() const { return vertices; }

	void transform(const Math::Matrix4d<float>& matrix);

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
	const unsigned int id;
	VertexCollection vertices;
	FaceCollection faces;
};

	}
}

#endif