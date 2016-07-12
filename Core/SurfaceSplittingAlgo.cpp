#include "stdafx.h"
#include "SurfaceSplittingAlgo.h"
#include "Edge.h"
#include "Vertex.h"

using namespace Crystal::Core;


void SurfaceSplittingAlgo::splitByCenter(Face* f)
{
	Vertex* center = surface->createVertex( f->getCenterPoint() );
	surface->createFace(f->getV1(), f->getV2(), center);
	surface->createFace(f->getV2(), f->getV1(), center);
}

void SurfaceSplittingAlgo::splitByBottom(Face* f)
{
	/*
	auto bottom = nodes.create(f->getEdges()[1]->getMidPoint());
	auto f2 = createTriangleFace(bottom, f->getEdges()[2]->getStart(), f->getEdges()[2]->getEnd());

	f->getEdges()[1]->changeEnd(bottom);
	f->getEdges()[2]->changeStart(bottom);
	f->getEdges()[2]->changeEnd(f->getEdges()[0]->getStart());
	assert(f->getArea() > 0);

	assert( f2->getArea() > 0);

	surface->add(faces.get());
	surface->add(nodes.get());
	surface->add(edges.get());
	SurfaceFactory fa(nodes, edges, faces);
	factory->merge(fa);
	for (auto f : surface->getFaces()) {
		assert(f->isConnected());
	}
	*/
}

