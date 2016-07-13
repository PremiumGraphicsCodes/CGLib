#include "stdafx.h"
#include "PolygonFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

PolygonFactory::PolygonFactory() :
	nextId(0)
{
}

PolygonFactory::~PolygonFactory()
{
	clear();
}

void PolygonFactory::clear()
{
	for (auto p : polygons) {
		delete p;
	}
	polygons.clear();
	nextId = 0;
}

PolygonMesh* PolygonFactory::create(const Curve3d<float>& curve)
{
	auto polygon = new PolygonMesh();
	polygon->create(curve, nextId++);
	return polygon;
}

PolygonMesh* PolygonFactory::create(const CircularCurve3d<float>& curve)
{
	auto polygon = new PolygonMesh();
	polygon->create(curve, nextId++);
	return polygon;
}


PolygonMesh* PolygonFactory::create(const TriangleCurve3d<float>& curve)
{
	auto polygon = new PolygonMesh();
	polygon->create(curve, nextId++);
	return polygon;
}
