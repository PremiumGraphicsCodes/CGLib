#include "TriangleMesh.h"

#include "Vertex.h"
#include "TriangleFace.h"

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
			delete v2;
			return true;
		}
		return false;
	}
}


TriangleMesh::~TriangleMesh()
{
	clear();
}

bool TriangleMesh::hasVertex(Vertex* v)
{
	return (std::find(vertices.begin(), vertices.end(), v) != vertices.end());
}

void TriangleMesh::sortVertices()
{
	vertices.sort(::comp);
	vertices.unique(::isSame);
	int nextId = 0;
	for (auto v : vertices) {
		v->id = nextId++;
	}
}

Vertex* TriangleMesh::createVertex(const Vector3d<float>& position)
{
	auto v = new Vertex(position, nextIndexId++);
	vertices.push_back(v);
	return v;
}


TriangleFace* TriangleMesh::createFace(Vertex* v1, Vertex* v2, Vertex* v3)
{
	auto f = new TriangleFace(v1, v2, v3);
	faces.push_back(f);
	return f;
}

void TriangleMesh::add(const Triangle<float>& triangle)
{
	auto v1 = createVertex( triangle.getv0() );
	auto v2 = createVertex( triangle.getv1() );
	auto v3 = createVertex( triangle.getv2() );
	auto f = createFace(v1, v2, v3);
	v1->setFace(f);
	v2->setFace(f);
	v3->setFace(f);
}


void TriangleMesh::clear()
{
	for (auto v : vertices) {
		delete v;
	}
	vertices.clear();
	for (auto f : faces) {
		delete f;
	}
	faces.clear();
}
