#include "stdafx.h"
#include "SurfaceSplittingAlgo.h"
#include "Edge.h"
#include "Vertex.h"

using namespace Crystal::Core;

void SurfaceSplittingAlgo::splitByNode(TriFace* f)
{
	const auto& es = f->toEdges();
	std::vector<Vertex*> startPoints;
	std::vector<Vertex*> midPoints;
	for (const auto& e : es) {
		startPoints.push_back(e.getStart());
		surface->createVertex(e.getMidPoint());
	}
	f->getV2()->moveTo(midPoints[0]->getPosition());
	f->getV3()->moveTo(midPoints[1]->getPosition());
	surface->createFace(midPoints[0], startPoints[1], midPoints[1]);
	surface->createFace(midPoints[1], startPoints[2], midPoints[2]);
	surface->createFace(midPoints[0], startPoints[1], midPoints[2]);
}

void SurfaceSplittingAlgo::splitByCenter(TriFace* f)
{
	Vertex* center = surface->createVertex( f->getCenterPoint() );
	surface->createFace(f->getV1(), f->getV2(), center);
	surface->createFace(f->getV2(), f->getV1(), center);
}

void SurfaceSplittingAlgo::splitByBottom(TriFace* f)
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

