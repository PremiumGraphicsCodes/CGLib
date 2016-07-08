#include "stdafx.h"
#include "SurfaceSplittingAlgo.h"
#include "Face.h"
#include "Edge.h"
#include "Node.h"
#include "Surface.h"

using namespace Crystal::Core;

void SurfaceSplittingAlgo::splitByNode(Face* f)
{
	const auto& es = f->getEdges();
	std::vector<Node*> startPoints;
	std::vector<Node*> midPoints;
	for (const auto& e : es) {
		startPoints.push_back(e->getStart());
		midPoints.push_back(nodes.create(e->getMidPoint()));
	}
	f->getEdges()[0]->changeEnd(midPoints[0]);
	f->getEdges()[1]->changeStart(midPoints[0]);
	f->getEdges()[1]->changeEnd(midPoints[2]);
	f->getEdges()[2]->changeStart(midPoints[2]);
	//createTriangleFace(startPoints[0], midPoints[0], midPoints[2]);
	createTriangleFace(midPoints[0], startPoints[1], midPoints[1]);
	createTriangleFace(midPoints[1], startPoints[2], midPoints[2]);
	createTriangleFace(midPoints[0], midPoints[1], midPoints[2]);
	surface->add(this->faces.get());
	surface->add(this->nodes.get());
	surface->add(this->edges.get());
	SurfaceFactory fa(nodes, edges, faces);
	factory->merge(fa);
}

void SurfaceSplittingAlgo::splitByCenter(Face* f)
{
	Node* center = nodes.create( f->getCenterPoint() );
	createTriangleFace(f->getEdges()[0]->getStart(), f->getEdges()[0]->getEnd(), center);
	createTriangleFace(f->getEdges()[1]->getStart(), f->getEdges()[1]->getEnd(), center);
	createTriangleFace(f->getEdges()[2]->getStart(), f->getEdges()[2]->getEnd(), center);
	surface->add(this->faces.get());
	surface->add(this->nodes.get());
	surface->add(this->edges.get());
	SurfaceFactory fa(nodes, edges, faces);
	factory->merge(fa);
}


Face* SurfaceSplittingAlgo::createTriangleFace(Node* n1, Node* n2, Node* n3)
{
	auto e1 = edges.create(n1, n2);
	auto e2 = edges.create(n2, n3);
	auto e3 = edges.create(n3, n1);
	return faces.create(e1, e2, e3);
}
