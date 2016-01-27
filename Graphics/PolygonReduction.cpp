#include "PolygonReduction.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics::Experiment;


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

	bool compare(std::shared_ptr<Vertex> lhs, std::shared_ptr<Vertex> rhs)
	{
		const auto h1 = toHash(lhs->getPosition());
		const auto h2 = toHash(rhs->getPosition());
		return h1 < h2;
	}

	bool isSamePosition(std::shared_ptr<Vertex> lhs, std::shared_ptr<Vertex> rhs)
	{
		return lhs->getPosition() == rhs->getPosition();
	}
}


float Edge::getLength() const
{
	return v2->getPosition().getDistance( v1->getPosition() );
}

bool TriangleFace::hasVertex(const std::shared_ptr<Vertex>& v)
{
	return std::find(vertices.begin(),vertices.end(), v) != vertices.end();
}



void TriangleFace::replaceVertex(std::shared_ptr<Vertex> v1, std::shared_ptr<Vertex> v2)
{
	auto pos = std::find(vertices.begin(), vertices.end(), v1);
	*pos = v2;
}

TriangleMesh::~TriangleMesh()
{
	clear();
}

std::shared_ptr<Vertex> TriangleMesh::createVertex(const Vector3d<float>& position)
{
	auto v = std::make_shared< Vertex >(position);
	vertices.push_back(v);
	return v;
}

std::shared_ptr<TriangleFace> TriangleMesh::createFace(const std::array< std::shared_ptr<Vertex>, 3>& vertices)
{
	auto f = std::make_shared< TriangleFace >(vertices);
	faces.push_back(f);
	edges.push_back(std::make_shared<Edge>(vertices[0], vertices[1]));
	edges.push_back(std::make_shared<Edge>(vertices[1], vertices[2]));
	edges.push_back(std::make_shared<Edge>(vertices[2], vertices[0]));
	return f;
}

void TriangleMesh::clear()
{
	vertices.clear();
	edges.clear();
	faces.clear();
}

void TriangleMesh::removeOverlappedVerticies()
{
	vertices.sort(compare);
	vertices.unique(isSamePosition);
	/*
	for (auto v : vertices) {
		v->getPo
	}
	*/
}
