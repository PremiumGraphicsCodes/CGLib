#ifndef __CRYSTAL_CORE_FACE_H__
#define __CRYSTAL_CORE_FACE_H__

#include <vector>
#include "../Math/Vector3d.h"
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Core {

class Edge;

class Face : private UnCopyable
{
public:
	//Face() = default;

	Face(const std::vector<Edge*>& edges, int id) :
		edges(edges),
		id( id)
	{}

	float getArea() const;

	Math::Vector3d<float> getNormal() const;

private:
	std::vector<Edge*> edges;
	const int id;
};
	}
}

#endif