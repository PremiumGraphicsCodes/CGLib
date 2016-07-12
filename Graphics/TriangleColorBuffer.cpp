#include "stdafx.h"
#include "TriangleColorBuffer.h"


using namespace Crystal::Math;
using namespace Crystal::Core;
using namespace Crystal::Graphics;

TriangleColorBuffer::TriangleColorBuffer() :
	nextId(0)
{
}

void TriangleColorBuffer::clear()
{
	indices.clear();
	positions.clear();
	colors.clear();
	nextId = 0;
}

void TriangleColorBuffer::add(const PolygonMesh& mesh, const ColorRGBA<float>& color)
{
	auto si = mesh.toIndices();
	for (auto& s : si) {
		s += nextId;
	}
	this->indices.insert(indices.end(), si.begin(), si.end());
	const auto& nodes = mesh.getVertices();
	for (auto& n : nodes) {
		add(*n, color);
	}
	nextId += mesh.getVertices().size();
}


void TriangleColorBuffer::add(const Point3d<float>& point, const ColorRGBA<float>& color)
{
	this->positions.add(point.getPosition());
	this->colors.add(color);
}
