#ifndef __CRYSTAL_POLYGON_TRIANGLE_FACE_H__
#define __CRYSTAL_POLYGON_TRIANGLE_FACE_H__

#include "../Math/Vector3d.h"


namespace Crystal {
	namespace Polygon {

class Vertex;

class TriangleFace
{
public:
	TriangleFace(Vertex* v1, Vertex* v2, Vertex* v3) :
		v1(v1),
		v2(v2),
		v3(v3)
	{
		this->normal = (v2->getPosition() - v1->getPosition()).getOuterProduct(v3->getPosition() - v1->getPosition());
		this->normal.normalize();
	}

	Vertex* find(Vertex* v) {
		if (v == v1) {
			return v1;
		}
		if (v == v2) {
			return v2;
		}
		if (v == v3) {
			return v3;
		}
		assert(false);
		return nullptr;
	}

	void replace(Vertex* oldVertex, Vertex* newVertex) {
		if (oldVertex == v1) {
			v1 = newVertex;
		}
		else if (oldVertex == v2) {
			v2 = newVertex;
		}
		else if (oldVertex == v3) {
			v3 = newVertex;
		}
		else {
			assert(false);
		}
	}


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

	}
}

#endif