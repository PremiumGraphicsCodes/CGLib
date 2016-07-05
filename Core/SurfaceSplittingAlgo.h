#ifndef __CRYSTAL_CORE_SURFACE_SPLITTING_ALGO_H__
#define __CRYSTAL_CORE_SURFACE_SPLITTING_ALGO_H__

#include "SurfaceFactory.h"

#include "NodeCollection.h"
#include "EdgeCollection.h"
#include "FaceCollection.h"

namespace Crystal {
	namespace Core {

class SurfaceSplittingAlgo
{
public:

	SurfaceSplittingAlgo(Surface* s, SurfaceFactory* f) :
		surface(s),
		factory(f)
	{}

	void splited(Face* f);

private:
	Face* createTriangleFace(Node* n1, Node* n2, Node* n3);

	Surface* surface;
	SurfaceFactory* factory;

	NodeCollection nodes;
	EdgeCollection edges;
	FaceCollection_ faces;

};

	}
}
#endif