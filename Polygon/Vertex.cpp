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

}

TriangleMesh::~TriangleMesh()
{
	clear();
}

bool TriangleMesh::hasVertex(Vertex* v)
{
	return (std::find(vertices.begin(), vertices.end(), v) != vertices.end());
}

Vertex* TriangleMesh::createVertex(const Vector3d<float>& position)
{
	auto v = new Vertex(position);
	vertices.push_back(v);
	return v;
}

TriangleFace* TriangleMesh::createFace(Vertex* v1, Vertex* v2, Vertex* v3)
{
	auto f = new TriangleFace(v1, v2, v3);
	faces.push_back(f);
	return f;
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