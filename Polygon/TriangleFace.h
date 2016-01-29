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