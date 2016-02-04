#include "PolygonObjectBuilder.h"
#include "PolygonObject.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

PolygonObject* PolygonObjectBuilder::build(const Box<float>& box)
{
	/*
	const auto minx = box.getMinX();
	const auto miny = box.getMinY();
	const auto minz = box.getMinZ();
	const auto maxx = box.getMaxX();
	const auto maxy = box.getMaxY();
	const auto maxz = box.getMaxZ();

	PolygonObject* object = new PolygonObject();
	auto p1 = object->createPosition(Vector3d<float>(minx, miny, minz));
	auto p2 = object->createPosition(Vector3d<float>(maxx, miny, minz));
	auto p3 = object->createPosition(Vector3d<float>(maxx, maxy, minz));
	auto p4 = object->createPosition(Vector3d<float>(minx, maxy, minz));
	auto p5 = object->createPosition(Vector3d<float>(minx, miny, maxz));
	auto p6 = object->createPosition(Vector3d<float>(maxx, miny, maxz));
	auto p7 = object->createPosition(Vector3d<float>(maxx, maxy, maxz));
	auto p8 = object->createPosition(Vector3d<float>(minx, maxy, maxz));

	auto n1 = object->createNormal(Vector3d<float>(0.0, 0.0, -1.0));
	auto n2 = object->createNormal(Vector3d<float>(0.0, 0.0, 1.0));
	auto n3 = object->createNormal(Vector3d<float>(-1.0, 0.0, 0.0));

	auto v1 = object->createVertex(p1, n1);
	auto v2 = object->createVertex(p2, n1);
	auto v3 = object->createVertex(p3, n1);
	auto v4 = object->createVertex(p4, n1);
	auto v5 = object->createVertex(p5, n2);
	auto v6 = object->createVertex(p6, n2);
	auto v7 = object->createVertex(p7, n2);
	auto v8 = object->createVertex(p8, n2);

	object->createFaces({ v1, v2, v3, v4 });
	object->createFaces({ v8, v7, v6, v5 });
	object->createFaces({ v1, v2, v6, v5 });
	*/
	return nullptr;
}
