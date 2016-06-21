#include "stdafx.h"
#include "VisualPolygon.h"

using namespace Crystal::Graphics;
using namespace Crystal::Core;


VisualPolygon::VisualPolygon() : polygon(nullptr)
{}


VisualPolygon::VisualPolygon(PolygonMesh* polygon)
	: polygon(polygon)
{
}