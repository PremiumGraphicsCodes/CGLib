#include "PolygonReduction.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics::Experiment;

float Vertex::computeCost()
{
	if (neighbors.empty()) {
		this->collapse = nullptr;
		return 0.0f;
	}
	cost = 100000;
	this->collapse = nullptr;
	for (auto v : neighbors) {
		const auto e = Edge(this, v);
		const auto c = e.computeCost();
		if (c < this->cost) {
			this->collapse = v;
			this->cost = c;
		}
	}
	return this->cost;
}

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

	bool compare(Vertex* lhs, Vertex* rhs)
	{
		const auto h1 = toHash(lhs->getPosition());
		const auto h2 = toHash(rhs->getPosition());
		return h1 < h2;
	}

	bool isSamePosition(Vertex* lhs, Vertex* rhs)
	{
		return lhs->getPosition() == rhs->getPosition();
	}
}

float Edge::computeCost() const
{
	float curvature = 0.0f;

	std::list<TriangleFace*> sides;
	const auto& faces = v1->getFaces();
	for (auto f : faces) {
		if (f->hasVertex(v2)) {
			sides.push_back(f);
		}
	}

	for (auto f1 : faces) {
		float minCurvature = 1.0f;
		for (auto& f2 : sides) {
			const float innerProduct = f1->getNormal().getInnerProduct(f2->getNormal());
			minCurvature = std::min<float>(minCurvature, (1.0f - innerProduct) / 2.0f);
		}
		curvature = std::max<float>(curvature, minCurvature);
	}

	float length = getLength();
	return length * curvature;
}

float Edge::getLength() const
{
	return v2->getPosition().getDistance( v1->getPosition() );
}

bool TriangleFace::hasVertex(const Vertex* v)
{
	return std::find(vertices.begin(),vertices.end(), v) != vertices.end();
}

void TriangleFace::replaceVertex(Vertex* v1, Vertex* v2)
{
	auto pos = std::find(vertices.begin(), vertices.end(), v1);
	*pos = v2;
}

TriangleMesh::~TriangleMesh()
{
	clear();
}

Vertex* TriangleMesh::createVertex(const Vector3d<float>& position)
{
	auto v = new Vertex(position);
	vertices.push_back(v);
	return v;
}

TriangleFace* TriangleMesh::createFace(const std::array< Vertex*, 3>& vertices)
{
	auto f = new TriangleFace(vertices);
	faces.push_back(f);
	return f;
}

void TriangleMesh::clear()
{
	for (auto v : vertices) {
		delete v;
	}
	vertices.clear();
	for (auto e : edges) {
		delete e;
	}
	edges.clear();
	for (auto f : faces) {
		delete f;
	}
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


void TriangleMesh::reduceTo(const int desired)
{
	while (vertices.size() < desired) {
		Edge* e = getMinimunCostEdge();
		e->collapse();
	}
}

void Edge::collapse()
{
	if (!v2) {
		auto v1 = this->v1;
		delete v1;
		return;
	}

	auto neighbors = v1->getNeighbors();
	auto faces = v1->getFaces();
	for (std::list<TriangleFace*>::reverse_iterator iter = faces.rbegin(); iter != faces.rend(); iter++) {
		auto face = *iter;
		if (face->hasVertex(v1)) {
			delete face;
		}
	}
	for (std::list<TriangleFace*>::reverse_iterator iter = faces.rbegin(); iter != faces.rend(); iter++) {
		auto face = *iter;
		face->replaceVertex(v1, v2);
	}
	delete v1;
	for (auto n : neighbors) {
		n->computeCost();
	}
}

Edge* TriangleMesh::getMinimunCostEdge()
{
	float minCost = 100000;
	Edge* minCostEdge = edges.front();
	for (auto e : edges) {
		auto c = e->computeCost();
		if (c < minCost) {
			minCostEdge = e;
			minCost = c;
		}
	}
	return minCostEdge;
}
