#ifndef __CRYSTAL_POLYGON_FACE_H__
#define __CRYSTAL_POLYGON_FACE_H__

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Polygon {

class Vertex;

class Face
{
public:
	Face(Vertex* v1, Vertex* v2, Vertex* v3);

	Vertex* find(Vertex* v);

	void replace(Vertex* oldVertex, Vertex* newVertex);


	Vertex* getV1() const { return v1; }

	Vertex* getV2() const { return v2; }

	Vertex* getV3() const { return v3; }

	Math::Vector3d<float> getNormal() const { return normal; }

	void replaceVertex(Vertex* v1, Vertex* v2);

private:
	Vertex* v1;
	Vertex* v2;
	Vertex* v3;

	Math::Vector3d<float> normal;
};

class FaceCollection
{
public:
	FaceCollection()
	{}

	FaceCollection(const std::vector<Face*>& faces) :
		faces(faces)
	{}

	~FaceCollection() {
	}

	void add(const FaceCollection& rhs);

	Face* create(Vertex* v1, Vertex* v2, Vertex* v3) {
		auto f = new Face(v1, v2, v3);
		faces.push_back(f);
		return f;
	}

	void clear() {
		for (auto f : faces) {
			delete f;
		}
		faces.clear();
	}

	using iterator = std::vector<Face*>::iterator;
	using const_iterator = std::vector<Face*>::const_iterator;

	iterator begin() { return faces.begin(); }

	const_iterator begin() const { return faces.begin(); }

	iterator end() { return faces.end(); }

	const_iterator end() const { return faces.end(); }

	size_t size() const { return faces.size(); }

	Face* operator[](const int i) const { return faces[i]; }

private:
	std::vector<Face*> faces;

};
	}
}

#endif