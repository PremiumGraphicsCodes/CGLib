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
