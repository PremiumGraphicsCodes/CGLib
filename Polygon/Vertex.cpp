#include "Vertex.h"
#include "Face.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

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
			auto face = v2->getFace();
			face->replace(v2, v1);
			v1->normalize(*v2);
			delete v2;
			return true;
		}
		return false;
	}
}

Vertex::Vertex(const unsigned int id, const Vector3d<float>& position) :
	id(id),
	position(position)
{}

Vertex::Vertex(const unsigned int id, const Vector3d<float>& position, const Vector3d<float>& normal) :
	id(id),
	position(position),
	normal(normal)
{}

Vertex::Vertex(const unsigned int id, const Vector3d<float>& position, const Vector3d<float>& normal, const Vector3d<float>& texCoord) :
	id(id),
	position(position),
	normal(normal),
	texCoord(texCoord)
{}

void Vertex::normalize(const Vertex& rhs)
{
	this->normal = normal * 0.5f + rhs.normal * 0.5f;
	this->normal.normalize();
}

VertexCollection::VertexCollection() : nextId(0)
{}

VertexCollection::VertexCollection(const std::vector<Vertex*>& vertices) :
	vertices(vertices),
	nextId(0)
{}

VertexCollection::~VertexCollection()
{
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
		v->id = nextId++;
	}
	vertices = std::vector<Vertex*>(vlist.begin(), vlist.end());
}

Vertex* VertexCollection::create(Vector3d<float> position, Vector3d<float> normal, Vector3d<float> texCoord)
{
	auto v = new Vertex(nextId++, position, normal, texCoord);
	vertices.push_back(v);
	return v;
}

void VertexCollection::merge(VertexCollection& rhs)
{
	vertices.insert(vertices.end(), rhs.vertices.begin(), rhs.vertices.end());
	int nextId = 0;
	for (auto v : vertices) {
		v->id = nextId++;
	}
	rhs.vertices.clear();
}

void VertexCollection::clear()
{
	for (auto v : vertices) {
		delete v;
	}
	vertices.clear();
}
