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
		return toHash(*v1->position) < toHash(*v2->position);
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

Vector3d<float>* TriangleMesh::createPosition(const Vector3d<float>& position)
{
	auto v = new Vector3d<float>(position);
	positions.push_back(v);
	return v;
}

Vector3d<float>* TriangleMesh::createNormal(const Vector3d<float>& normal)
{
	auto n = new Vector3d<float>(normal);
	normals.push_back(n);
	return n;
}

Vector3d<float>* TriangleMesh::createTexCoord(const Vector3d<float>& texCoord)
{
	auto t = new Vector3d<float>(texCoord);
	texCoords.push_back(t);
	return t;
}


Vertex* TriangleMesh::createVertex(Vector3d<float>* position, Vector3d<float>* normal)
{
	auto v = new Vertex();
	v->position = position;
	v->normal = normal;
	v->id = nextIndexId++;
	vertices.push_back(v);
	return v;
}


TriangleFace* TriangleMesh::createFace(Vertex* v1, Vertex* v2, Vertex* v3)
{
	auto f = new TriangleFace(v1, v2, v3);
	faces.push_back(f);
	return f;
}

TriangleFace* TriangleMesh::createFace(const int vindex1, const int vindex2, const int vindex3)
{
	std::vector<Vertex*> vs(vertices.begin(), vertices.end());
	auto v1 = vs[vindex1];
	auto v2 = vs[vindex2];
	auto v3 = vs[vindex3];
	return createFace(v1, v2, v3);
}

std::list< TriangleFace* > TriangleMesh::createFaces(const std::vector<int>& ids)
{
	std::list< TriangleFace* > fs;
	std::vector<Vertex*> vs(vertices.begin(), vertices.end());
	const auto origin = ids[0];
	for (size_t i = 1; i < ids.size()-1; i++) {
		auto id1 = ids[i];
		auto id2 = ids[i + 1];
		fs.push_back( createFace(vs[origin], vs[id1], vs[id2]) );
	}
	return fs;
}


void TriangleMesh::add(const Triangle<float>& triangle)
{
	auto n = createNormal( triangle.getNormal() );
	auto p1 = createPosition(triangle.getv0());
	auto p2 = createPosition(triangle.getv1());
	auto p3 = createPosition(triangle.getv2());

	auto v1 = createVertex( p1, n );
	auto v2 = createVertex( p1, n );
	auto v3 = createVertex( p3, n );
	auto f = createFace(v1, v2, v3);
	v1->f = (f);
	v2->f = (f);
	v3->f = (f);
}


void TriangleMesh::clear()
{
	for (auto p : positions) {
		delete p;
	}
	positions.clear();
	for (auto n : normals) {
		delete n;
	}
	normals.clear();
	for (auto t : texCoords) {
		delete t;
	}
	texCoords.clear();
	for (auto v : vertices) {
		delete v;
	}
	vertices.clear();
	for (auto f : faces) {
		delete f;
	}
	faces.clear();

}
