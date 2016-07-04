#ifndef __CRYSTAL_CORE_SMOOTHING_ALGO_H__
#define __CRYSTAL_CORE_SMOOTHING_ALGO_H__

#include "SurfaceFactory.h"

#include "NodeCollection.h"
#include "EdgeCollection.h"
#include "FaceCollection.h"

namespace Crystal {
	namespace Core {
		class Node;

class SmoothingAlgo
{
public:
	SmoothingAlgo(Surface* s, SurfaceFactory* f) :
		surface(s),
		factory(f)
	{}

	void execute(Node* n);

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