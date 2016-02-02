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
	Vertex() :
		position(nullptr),
		normal(nullptr),
		texCoord(nullptr),
		id(-1)
	{}

	int id;

	Math::Vector3d<float>* getPosition() { return position; }

	Math::Vector3d<float> getPosition() const { return *position; }


	int getId() const { return id; }

	Math::Vector3d<float>* position;
	Math::Vector3d<float>* normal;
	Math::Vector3d<float>* texCoord;
	TriangleFace* f;
};


	}
}
#endif
