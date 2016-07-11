#ifndef __CRYSTAL_CORE_REDUCTION_ALGO_H__
#define __CRYSTAL_CORE_REDUCTION_ALGO_H__

#include "SurfaceFactory.h"

#include "NodeCollection.h"
#include "EdgeCollection.h"
#include "FaceCollection.h"

namespace Crystal {
	namespace Core {

class ReductionAlgo
{
public:

	ReductionAlgo(Surface* s, SurfaceFactory* f) :
		surface(s),
		factory(f)
	{}

	void execute();

	void execute(Edge* e);

	float getCollapseCost(Edge* edge);

	float getCost(Node* n);

private:
	Surface* surface;
	SurfaceFactory* factory;
};

	}
}
#endif