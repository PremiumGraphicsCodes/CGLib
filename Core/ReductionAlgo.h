#ifndef __CRYSTAL_CORE_REDUCTION_ALGO_H__
#define __CRYSTAL_CORE_REDUCTION_ALGO_H__

#include "PolygonMesh.h"


namespace Crystal {
	namespace Core {

class ReductionAlgo
{
public:

	ReductionAlgo(PolygonMesh* s) :
		surface(s)
	{}

	void execute();

	void execute(Edge* e);

	float getCollapseCost(Edge* edge);

	float getCost(Vertex* n);

private:
	PolygonMesh* surface;
};

	}
}
#endif