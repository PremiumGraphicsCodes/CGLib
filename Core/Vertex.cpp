#include "stdafx.h"
#include "Vertex.h"
#include "Face.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Vertex::Vertex(const Point3d<float>& point, const unsigned int id) :
	Point3d<float>(point),
	id(id)
{
}


Vertex::Vertex(const Vector3d<float>& position, const unsigned int id) :
	Point3d<float>(position),
	id(id)
{}

Vertex::Vertex(const Vector3d<float>& position, const Vector3d<float>& normal, const unsigned int id) :
	Point3d<float>(position, normal),
	id(id)
{}

Vertex::Vertex(const Vector3d<float>& position, const Vector3d<float>& normal, const Vector2d<float>& texCoord, const unsigned int id) :
	Point3d<float>(position, normal, texCoord),
	id(id)
{}


Vertex* Vertex::clone()
{
	return new Vertex(getPosition(), getNormal(), getParameter(), id);
}

#include "Edge.h"

float Vertex::calculateCollapseCost()
{
	float cost = FLT_MAX;
	auto neighbors = getNeighbors();
	for (auto n : neighbors) {
		Edge e(this, n, 0);
		auto c = e.calculateCollapseCost();
		if (c < cost) {
			cost = c;
		}
	}
	return cost;
}

std::list<Vertex*> Vertex::getNeighbors() const
{
	std::list<Vertex*> neighbors;
	for (auto f : faces) {
		if (f->getV1() != this) {
			neighbors.push_back(f->getV1());
		}
		if (f->getV2() != this) {
			neighbors.push_back(f->getV2());
		}
		if (f->getV3() != this) {
			neighbors.push_back(f->getV3());
		}
	}
	neighbors.sort();
	neighbors.unique();
	return neighbors;
}

std::list<Vertex*> Vertex::getNeighbors(const float length) const
{
	auto neighbors = getNeighbors();
	for (auto n : neighbors) {
		if (n->getPosition().getDistanceSquared(this->getPosition()) < length * length) {
			neighbors.push_back(n);
		}
	}
	neighbors.sort();
	neighbors.unique();
	return neighbors;
}

void Vertex::merge(Vertex* rhs)
{
	inEdges.insert(inEdges.end(), rhs->inEdges.begin(), rhs->inEdges.end());
	outEdges.insert(outEdges.end(), rhs->outEdges.begin(), rhs->outEdges.end());
	for (auto in : inEdges) {
		in->changeEnd(this);
	}
	for (auto out : outEdges) {
		out->changeStart(this);
	}
	
}
