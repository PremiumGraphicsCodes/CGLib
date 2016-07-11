#include "stdafx.h"
#include "SurfaceRemoveAlgo.h"

#include "SurfaceFactory.h"
#include "Surface.h"
#include "Face.h"
#include "Edge.h"
#include "Node.h"

using namespace Crystal::Core;

SurfaceRemoveAlgo::SurfaceRemoveAlgo(SurfaceFactory* factory)
	: factory(factory)
{}

void SurfaceRemoveAlgo::add(Face *f)
{
	faces.push_back(f);
}

void SurfaceRemoveAlgo::add(Edge* e)
{
	edges.push_back(e);
}

void SurfaceRemoveAlgo::add(Node* n)
{
	nodes.push_back(n);
}

void SurfaceRemoveAlgo::execute()
{
	for (auto n : nodes) {
		factory->remove(n);
	}
	for (auto e : edges) {
		faces.push_back(e->getFace());
		factory->remove(e);
	}
	for (auto f : faces) {
		factory->remove(f);
		factory->remove(f->getEdges()[0]);
		factory->remove(f->getEdges()[1]);
		factory->remove(f->getEdges()[2]);

	}
	factory->cleaning();
}