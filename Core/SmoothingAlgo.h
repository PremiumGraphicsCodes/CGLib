#ifndef __CRYSTAL_CORE_SMOOTHING_ALGO_H__
#define __CRYSTAL_CORE_SMOOTHING_ALGO_H__

#include "PolygonMesh.h"

#include "NodeCollection.h"

namespace Crystal {
	namespace Core {
		class Vertex;

class SmoothingAlgo
{
public:
	SmoothingAlgo(PolygonMesh* s) :
		surface(s)
	{}

	void execute(Vertex* n);

private:

	PolygonMesh* surface;

};

	}
}
#endif