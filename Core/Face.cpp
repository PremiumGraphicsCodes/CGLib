#include "stdafx.h"

#include "Face.h"

#include "Node.h"
#include "Edge.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Face::Face(const std::array<Edge*, 3>& edges, int id) :
	edges(edges),
	id(id)
{
	for (auto e : edges) {
		if (e == nullptr) {
			continue;
		}
		e->setFace(this);
	}
}


float Face::getArea() const
{
	const auto v1 = edges[0]->getVector();
	const auto v2 = edges[1]->getVector();
	return v1.getOuterProduct(v2).getLength() * 0.5f;
}

bool Face::isCCW() const
{
	return getArea() > Tolerance<float>::getLooseTolerance();
}

bool Face::isCW() const
{
	return getArea() < -Tolerance<float>::getLooseTolerance();
}

Vector3d<float> Face::getNormal() const
{
	const auto v1 = edges[0]->getVector();
	const auto v2 = edges[1]->getVector();
	return v1.getOuterProduct(v2);
}

Vector3d<float> Face::getCenter() const
{
	Vector3d<float> pos;
	for (auto e : edges) {
		const auto n = e->getStart();
		pos += n->getPosition() / static_cast<float>( edges.size() );
	}
	return pos;
}

Point3d<float> Face::getCenterPoint() const
{
	Vector3d<float> pos;
	Vector3d<float> norm;
	Vector2d<float> param;
	for (auto e : edges) {
		const auto n = e->getStart();
		pos += n->getPosition() / static_cast<float>(edges.size());
		norm += n->getNormal() / static_cast<float>(edges.size());
		//param += n->getParameter() / static_cast<float>(edges.size());
	}
	return Point3d<float>(pos, norm, param);
}


Triangle3d<float> Face::toTriangle() const
{
	const auto v0 = edges[0]->getStart()->getPosition();
	const auto v1 = edges[1]->getStart()->getPosition();
	const auto v2 = edges[2]->getStart()->getPosition();
	return Triangle3d<float>(v0, v1, v2);
}

bool Face::hasIntersection(const Ray3d<float>& ray) const
{
	const auto& t = toTriangle();
	return ray.hasIntersection(t);
}

Vector3d<float> Face::getIntersection(const Ray3d<float>& ray) const
{
	const auto& t = toTriangle();
	return ray.getIntersection(t);
}

std::vector<unsigned int> Face::getNodeIds() const
{
	const unsigned int n1 = edges[0]->getStart()->getId();
	const unsigned int n2 = edges[1]->getStart()->getId();
	const unsigned int n3 = edges[2]->getStart()->getId();
	return {n1, n2, n3};
}

bool Face::has(Edge* e) const
{
	return ( std::find(edges.begin(), edges.end(), e) != edges.end() );
}

bool Face::isConnected() const
{
	for(auto iter = edges.begin(); iter != edges.end()-1; ++iter) {
		auto e1 = *(iter);
		auto e2 = *(iter + 1);
		if (e1 == nullptr || e2 == nullptr) {
			return false;
		}
		if (e1->getNext() != e2) {
			return false;
		}
	}
	return true;
}

bool Face::isCollapsed() const
{
	for (auto e : edges) {
		if (e == nullptr) {
			return true;
		}
	}
	for (auto e : edges) {
		if (e->isCollapsed()) {
			return true;
		}
	}
	return false;
}

bool Face::isDegenerated() const
{
	return getArea() == Tolerance<float>::getLooseTolerance();
}

