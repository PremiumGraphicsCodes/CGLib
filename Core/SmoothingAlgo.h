#ifndef __CRYSTAL_CORE_SMOOTHING_ALGO_H__
#define __CRYSTAL_CORE_SMOOTHING_ALGO_H__

#include "SurfaceFactory.h"

#include "NodeCollection.h"
#include "EdgeCollection.h"
#include "FaceCollection.h"

namespace Crystal {
	namespace Core {
		class Vertex;

class SmoothingAlgo
{
public:
	SmoothingAlgo(Surface* s, SurfaceFactory* f) :
		surface(s),
		factory(f)
	{}

	void execute(Vertex* n);

private:
	Face* createTriangleFace(Vertex* n1, Vertex* n2, Vertex* n3);

	Surface* surface;
	SurfaceFactory* factory;

	NodeCollection nodes;
	EdgeCollection edges;
	FaceCollection_ faces;
};

	}
}
#endif