#include "stdafx.h"
#include "Vertex.h"
#include "VertexRepository.h"
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


VertexRepository::VertexRepository() : nextId(0)
{}

VertexRepository::VertexRepository(const std::vector<Vertex*>& vertices):
nextId(0),
vertices(vertices.begin(), vertices.end())
{
}

VertexRepository::VertexRepository(const std::list<Vertex*>& vertices) :
	vertices(vertices),
	nextId(0)
{}

VertexRepository::~VertexRepository()
{
}

VertexRepository VertexRepository::clone()
{
	std::list<Vertex*> vs;
	for (auto v : vertices) {
		vs.push_back(v->clone());
	}
	return VertexRepository(vs);
}


bool VertexRepository::hasVertex(Vertex* v)
{
	return (std::find(vertices.begin(), vertices.end(), v) != vertices.end());
}


void VertexRepository::sort()
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

Vertex* VertexRepository::create(Vector3d<float> position, Vector3d<float> normal, Vector2d<float> texCoord)
{
	auto v = new Vertex(position, normal, texCoord, nextId++);
	vertices.push_back(v);
	return v;
}

Vertex* VertexRepository::create(const Point3d<float>& point)
{
	auto v = new Vertex(point.getPosition(), point.getNormal(), point.getParameter(), nextId++);
	vertices.push_back(v);
	return v;
}

Vertex* VertexRepository::findById(const int id) const
{
	for (auto v : vertices) {
		if (v->getId() == id) {
			return v;
		}
	}
	return nullptr;
}


void VertexRepository::merge(VertexRepository& rhs)
{
	vertices.insert(vertices.end(), rhs.vertices.begin(), rhs.vertices.end());
	renumber();
	rhs.vertices.clear();
}

void VertexRepository::clear()
{
	for (auto v : vertices) {
		delete v;
	}
	vertices.clear();
}

void VertexRepository::renumber()
{
	nextId = 0;
	for (auto v : vertices) {
		v->setId(nextId++);
	}
}

void VertexRepository::cleaning()
{
	renumber();
}


void VertexRepository::add(Vertex* v)
{
	vertices.push_back(v);
}

void VertexRepository::remove(Vertex* v)
{
	vertices.remove(v);
	delete v;
}


std::list<Vertex*> VertexRepository::find(const Vector3d<float>& position, const float radius)
{
	VertexSpaceHash hash(radius*2, static_cast<int>(vertices.size()));
	for (auto v : vertices) {
		hash.add(v);
	}
	return hash.getNeighbor(position);
}

Vertex* VertexRepository::findById(const int id)
{
	for (auto v : vertices) {
		if (id == v->getId()) {
			return v;
		}
	}
	return nullptr;
}
