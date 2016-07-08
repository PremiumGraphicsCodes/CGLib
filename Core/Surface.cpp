#include "stdafx.h"
#include "Surface.h"
#include "SurfaceFactory.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Surface::Surface() :
	id(-1)
{
}

Surface::Surface(const std::list<Node*>& nodes, const std::list<Edge*>& edges, const std::list<Face*>& faces, const int id) :
	nodes(nodes),
	edges(edges),
	faces(faces),
	id(id)
{
}

void Surface::add(const std::list<Node*>& nodes)
{
	this->nodes.insert(this->nodes.end(), nodes.begin(), nodes.end());
}

void Surface::add(const std::list<Edge*>& edges)
{
	this->edges.insert(this->edges.end(), edges.begin(), edges.end());
}

void Surface::add(const std::list<Face*>& faces)
{
	this->faces.insert(this->faces.end(), faces.begin(), faces.end());
}


void Surface::merge(Surface& rhs)
{
	add(rhs.faces);
	add(rhs.edges);
	add(rhs.nodes);
}


Surface::~Surface()
{
	clear();
}

void Surface::clear()
{
	faces.clear();
	edges.clear();
	nodes.clear();
}

std::vector<unsigned int> Surface::toIndices() const
{
	std::vector<unsigned int> indices;
	for (auto f : faces) {
		const auto& edges = f->getEdges();
		for (auto e : edges) {
			indices.push_back( e->getStart()->getId() );
		}
	}
	return indices;
}

std::vector<unsigned int> Surface::toFaceIds() const
{
	std::vector<unsigned int> indices;
	for (auto f : faces) {
		const auto& edges = f->getEdges();
		for (auto e : edges) {
			indices.push_back(f->getId());
		}
	}
	return indices;
}

void Surface::move(const Vector3d<float>& v)
{
	for (auto n : nodes) {
		n->move(v);
	}
}

void Surface::rotate(const Quaternion<float>& q)
{
	const auto& center = getCenter();
	move(-center);
	for (auto n : nodes) {
		n->transform(q.toMatrix());
	}
	move(center);
}

void Surface::scale(const Vector3d<float>& v)
{
	const auto& center = getCenter();
	move(-center);
	for (auto n : nodes) {
		n->scale(v);
	}
	move(center);

}


Vector3d<float> Surface::getCenter() const
{
	Vector3d<float> center;
	for (auto n : nodes) {
		center += n->getPosition() / nodes.size();
	}
	return center;
}

Box3d<float> Surface::getBoundingBox() const
{
	Box3d<float> bb(nodes.front()->getPosition());
	for (auto n : nodes) {
		bb.add(n->getPosition());
	}
	return bb;
}

Sphere<float> Surface::getBoundingSphere() const
{
	const auto& center = getCenter();
	float maxDist = -FLT_MAX;
	for (auto n : nodes) {
		const auto dist = n->getPosition().getDistance(center);
		maxDist = std::max<float>(maxDist, dist);
	}
	return Sphere<float>(center, maxDist);
}

std::vector<Vector3d<float>> Surface::getIntersections(const Ray3d<float>& ray) const
{
	std::vector<Vector3d<float>> intersections;
	for (auto f : faces) {
		if (f->hasIntersection(ray)) {
			intersections.push_back( f->getIntersection(ray) );
		}
	}
	return intersections;
}

Node* Surface::findNodeById(const int id)
{
	for (auto n : nodes) {
		if (n->getId() == id) {
			return n;
		}
	}
	return nullptr;
}

Face* Surface::findFaceById(const int id)
{
	for (auto f : faces) {
		if (f->getId() == id) {
			return f;
		}
	}
	return nullptr;
}

Edge* Surface::findEdgeById(const int id)
{
	for (auto e : edges) {
		if (e->getId() == id) {
			return e;
		}
	}
	return nullptr;

}


std::list<Node*> Surface::getNeighbor(Node* center, const float radius)
{
	std::list<Node*> results;
	for (auto n : nodes) {
		if (center->getPosition().getDistanceSquared(n->getPosition()) < radius * radius ) {
			results.push_back(n);
		}
	}
	return results;
}

bool Surface::has(const Node* node) const
{
	return std::find(nodes.begin(), nodes.end(), node) != nodes.end();
}

bool Surface::has(const Edge* edge) const
{
	return std::find(edges.begin(), edges.end(), edge) != edges.end();
}

bool Surface::has(const Face* face) const
{
	return std::find(faces.begin(), faces.end(), face) != faces.end();
}

void Surface::remove(Face* f)
{
	faces.remove(f);
}

void Surface::remove(Edge* e)
{
	edges.remove(e);
}

void Surface::remove(Node* n)
{
	nodes.remove(n);
}
