#ifndef __CRYSTAL_CORE_FACE_H__
#define __CRYSTAL_CORE_FACE_H__

#include <list>
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Core {

class Edge;

class Face : private UnCopyable
{
public:
	Face() = default;

	Face(const std::list<Edge*>& edges, int id) :
		edges(edges),
		id( id)
	{}

private:
	std::list<Edge*> edges;
	const int id;
};
	}
}

#endif