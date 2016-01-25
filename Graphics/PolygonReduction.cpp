#include "PolygonReduction.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics::Experiment;

float Edge::computeCost()
{
	float length = getLength();
	float curvature = 0.0f;

	std::list<TriangleFace*> sides;
	const auto& faces = v1->getFaces();
	for (TriangleFace* f : faces) {
		if (f->hasVertex(v2)) {
			sides.push_back(f);
		}
	}
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
	}
}