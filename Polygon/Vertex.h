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
	Vertex(const Math::Vector3d<float>& position, const unsigned int id) :
		position(position),
		id(id)
	{}

	Math::Vector3d<float> getPosition() const { return position; }

	Math::Vector3d<float> getNormal() const { return normal; }

	unsigned int getId() const { return id;  }

	void setFace(TriangleFace* f);

	TriangleFace* getFace() { return f; }

	unsigned int id;

private:
	Math::Vector3d<float> position;
	Math::Vector3d<float> normal;
	TriangleFace* f;
};


	}
}
#endif
