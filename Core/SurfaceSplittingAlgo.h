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

	void splitByNode(Face* f);

	void splitByCenter(Face* f);

	void splitByBottom(Face* f);

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