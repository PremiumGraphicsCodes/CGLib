#include "VisualPolygon.h"

#include "../Polygon/PolygonMesh.h"

using namespace Crystal::Graphics;
using namespace Crystal::Polygon;


VisualPolygon::VisualPolygon() : polygon(nullptr)
{}


VisualPolygon::VisualPolygon(PolygonMesh* polygon)
	: polygon(polygon)
{}