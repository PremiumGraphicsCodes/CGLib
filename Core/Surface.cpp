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
	int nextNodeId = nodes.size();
	for (auto n : rhs.nodes) {
		n->setId(nextNodeId++);
	}
	int nextEdgeId = edges.size();
	for (auto e : rhs.edges) {
		e->setId(nextEdgeId++);
	}
	int nextFaceId = faces.size();
	for (auto f : rhs.faces) {
		f->setId(nextFaceId++);
	}
	add(rhs.nodes);
	add(rhs.edges);
	add(rhs.faces);

	rhs.nodes.clear();
	rhs.edges.clear();
	rhs.faces.clear();
}


Surface::~Surface()
{
	clear();
}

void Surface::clear()
{
	for (auto f : faces) {
		delete f;
	}
	faces.clear();
	for (auto e : edges) {
		delete e;
	}
	edges.clear();
	for (auto n : nodes) {
		delete n;
	}
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

Surface* Surface::split(Face* f)
{
	const auto& es = f->getEdges();
	std::vector<Point3d<float>> startPoints;
	std::vector<Point3d<float>> midPoints;
	for (const auto& e : es) {
		startPoints.push_back(e->getStart()->clone());
		midPoints.push_back(e->getMidPoint());
	}

	TriangleCurve3d<float> curve(3);
	curve.set(0, 0, startPoints[0]);
	curve.set(1, 0, midPoints.front());
	curve.set(1, 1, midPoints.back());
	curve.set(2, 0, startPoints[1]);
	curve.set(2, 1, midPoints[1]);
	curve.set(2, 2, startPoints[2]);

	SurfaceFactory factory;
	return factory.create(curve);
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
