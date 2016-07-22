#include "stdafx.h"
#include "Face.h"
#include "Vertex.h"
#include "Edge.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Face::Face(Edge* e1, Edge* e2, Edge* e3, const int id) :
	id(id)
{
	edges[0] = e1;
	edges[1] = e2;
	edges[2] = e3;
}


Face::Face(const std::array<Edge*, 3>& edges, const int id) :
	edges( edges ),
	id(id)
{
	edges[0]->setFace(this);
	edges[1]->setFace(this);
	edges[2]->setFace(this);
}

Vertex* Face::find(Vertex* v)
{
	auto vertices = getVertices();
	auto f = std::find(vertices.begin(), vertices.end(), v);
	if (f != vertices.end()) {
		return v;
	}
	assert(false);
	return nullptr;
}

Vector3d<float> Face::getNormal() const
{
	auto vertices = getVertices();
	auto normal = (vertices[1]->getPosition() - vertices[0]->getPosition()).getOuterProduct(vertices[2]->getPosition() - vertices[0]->getPosition());
	normal.normalize();
	return normal;
}


Point3d<float> Face::getCenterPoint() const {
	auto vertices = getVertices();
	auto pos = (vertices[0]->getPosition() + vertices[1]->getPosition() + vertices[2]->getPosition()) / 3;
	return Point3d<float>(pos);
}

std::array< Edge*, 3 > Face::getEdges() const
{
	return edges;
}

std::array< Vertex*, 3 > Face::getVertices() const
{
	return{ edges[0]->getStart(), edges[1]->getStart(), edges[2]->getStart() };
}

bool Face::has(Vertex* v) const
{
	auto vertices = getVertices();
	auto f = std::find(vertices.begin(), vertices.end(), v);
	return (f != vertices.end());
}

float Face::getArea() const
{
	auto vertices = getVertices();
	auto v1 = (edges[0]->getEnd()->getPosition() - edges[0]->getStart()->getPosition());
	auto v2 = (edges[1]->getEnd()->getPosition() - edges[1]->getStart()->getPosition());
	return v1.getOuterProduct(v2).getLength() / 2.0f;
}

Orientation Face::getOrientation(const Vector3d<float>& pos) const
{
	auto inner = pos.getInnerProduct(getNormal());
	if (inner > Tolerance<float>::getLooseTolerance()) {
		return Orientation::CCW;
	}
	else if (inner < -Tolerance<float>::getLooseTolerance()) {
		return Orientation::CW;
	}
	else {
		return Orientation::None;
	}
}

bool Face::isDegenerated() const
{
	return getArea() < Tolerance<float>::getLooseTolerance();
}

void Face::toDegenerate()
{
	edges[0]->toDenerate();
	edges[1]->changeStart(edges[0]->getEnd());
	edges[1]->toDenerate();
	edges[2]->changeStart(edges[0]->getEnd());
	edges[2]->toDenerate();
	//edges[1]->toDenerate();
	//edges[2]->toDenerate();
}

std::map<Vertex*, Vertex*> Face::findDouble(const Face& rhs, const float distance)
{
	const auto& vertices1 = this->getVertices();
	const auto& vertices2 = rhs.getVertices();
	std::map<Vertex*, Vertex*> map;
	for (auto v1 : vertices1) {
		for (auto v2 : vertices2) {
			auto p1 = v1->getPosition();
			auto p2 = v2->getPosition();
			if (p1.getDistanceSquared(p2) < distance * distance) {
				map[v1] = v2;
			}
		}
	}
	return map;
}

void Face::mergeDouble(const Face& rhs, float distance)
{
	auto vertices1 = this->getVertices();
	auto doubles = findDouble(rhs, distance);
	for (auto d : doubles) {
		auto v1 = d.first;
		auto v2 = d.second;
		auto edges2 = rhs.getEdges();
		for (auto e2 : edges2) {
			if (e2->getStart() == v2) {
				e2->changeStart(v1);
			}
			if (e2->getEnd() == v2) {
				e2->changeEnd(v1);
			}
		}
	}
}

Triangle3d<float> Face::toTriangle() const
{
	auto vertices = getVertices();
	return Triangle3d<float>(vertices[0]->getPosition(), vertices[1]->getPosition(), vertices[2]->getPosition());
}
