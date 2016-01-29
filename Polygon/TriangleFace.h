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
	}

	Vertex* getV1() { return v1; }

	Vertex* getV2() { return v2; }

	Vertex* getV3() { return v3; }

	Math::Vector3d<float> getNormal() { return normal; }

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