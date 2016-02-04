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
		return toHash(v1->getPosition()->getVector()) < toHash(v2->getPosition()->getVector());
	}

	bool isSame(Vertex* v1, Vertex* v2)
	{
		if (v1->position == v2->position) {
			auto face = v2->f;
			face->replace(v2, v1);
			delete v2;
			return true;
		}
		return false;
	}
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

Vertex* VertexCollection::create(VectorId* position, VectorId* normal, VectorId* texCoord)
{
	auto v = new Vertex();
	v->position = position;
	v->normal = normal;
	v->texCoord = texCoord;
	v->id = nextId++;
	vertices.push_back(v);
	return v;
}
