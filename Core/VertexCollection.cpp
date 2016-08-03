#include "stdafx.h"
#include "Vertex.h"
#include "VertexCollection.h"
#include "VertexSpaceHash.h"
#include "Face.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

namespace {
	int toHash(const Vector3d<float>& pos)
	{
		const int p1 = 73856093;
		const int p2 = 19349663;
		const int p3 = 83492791;
		const int hashTableSize = 10000;
		const int x = static_cast<int>(pos.getX() * p1);
		const int y = static_cast<int>(pos.getY() * p2);
		const int z = static_cast<int>(pos.getZ() * p3);
		return  (x^y^z) % hashTableSize;
	}

	bool comp(Vertex* v1, Vertex* v2)
	{
		return toHash(v1->getPosition()) < toHash(v2->getPosition());
	}

	bool isSame(Vertex* v1, Vertex* v2)
	{
		if (v1->getPosition() == v2->getPosition()) {
			v1->normalize(*v2);
			//delete v2;
			//v2 = nullptr;
			return true;
		}
		return false;
	}
}


VertexCollection::VertexCollection() : nextId(0)
{}

VertexCollection::VertexCollection(const std::vector<Vertex*>& vertices):
nextId(0),
vertices(vertices.begin(), vertices.end())
{
}

VertexCollection::VertexCollection(const std::list<Vertex*>& vertices) :
	vertices(vertices),
	nextId(0)
{}

VertexCollection::~VertexCollection()
{
}

VertexCollection VertexCollection::clone()
{
	std::list<Vertex*> vs;
	for (auto v : vertices) {
		vs.push_back(v->clone());
	}
	return VertexCollection(vs);
}


bool VertexCollection::hasVertex(Vertex* v)
{
	return (std::find(vertices.begin(), vertices.end(), v) != vertices.end());
}


void VertexCollection::sort()
{
	std::list<Vertex*> vlist(vertices.begin(), vertices.end());
	vlist.sort(::comp);
	vlist.unique(::isSame);
	int nextId = 0;
	for (auto v : vlist) {
		v->setId( nextId++ );
	}
	vertices = std::list<Vertex*>(vlist.begin(), vlist.end());
	cleaning();
}

Vertex* VertexCollection::create(Vector3d<float> position, Vector3d<float> normal, Vector2d<float> texCoord)
{
	auto v = new Vertex(position, normal, texCoord, nextId++);
	vertices.push_back(v);
	return v;
}

Vertex* VertexCollection::create(const Point3d<float>& point)
{
	auto v = new Vertex(point.getPosition(), point.getNormal(), point.getParameter(), nextId++);
	vertices.push_back(v);
	return v;
}

Vertex* VertexCollection::findById(const int id) const
{
	for (auto v : vertices) {
		if (v->getId() == id) {
			return v;
		}
	}
	return nullptr;
}


void VertexCollection::merge(VertexCollection& rhs)
{
	vertices.insert(vertices.end(), rhs.vertices.begin(), rhs.vertices.end());
	renumber();
	rhs.vertices.clear();
}

void VertexCollection::clear()
{
	for (auto v : vertices) {
		delete v;
	}
	vertices.clear();
}

void VertexCollection::renumber()
{
	nextId = 0;
	for (auto v : vertices) {
		v->setId(nextId++);
	}
}

void VertexCollection::cleaning()
{
	renumber();
}


void VertexCollection::add(Vertex* v)
{
	vertices.push_back(v);
}

void VertexCollection::remove(Vertex* v)
{
	vertices.remove(v);
	delete v;
}


std::list<Vertex*> VertexCollection::find(const Vector3d<float>& position, const float radius)
{
	VertexSpaceHash hash(radius*2, static_cast<int>(vertices.size()));
	for (auto v : vertices) {
		hash.add(v);
	}
	return hash.getNeighbor(position);
}

Vertex* VertexCollection::findById(const int id)
{
	for (auto v : vertices) {
		if (id == v->getId()) {
			return v;
		}
	}
	return nullptr;
}
