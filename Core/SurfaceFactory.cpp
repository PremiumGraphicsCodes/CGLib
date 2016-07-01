#include "stdafx.h"
#include "SurfaceFactory.h"

#include "../Util/Array2d.h"
#include "NodeGrid.h"
#include "Surface.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

SurfaceFactory::~SurfaceFactory()
{
	clear();
}

void SurfaceFactory::clear()
{
	nodes.clear();
	edges.clear();
	faces.clear();
}

Surface* SurfaceFactory::create(const Curve3d<float>& curve, const int id)
{
	NodeGrid1d grid(curve.getUNumber(), curve.getVNumber());
	for (int u = 0; u < curve.getUNumber(); ++u) {
		for (int v = 0; v < curve.getVNumber(); ++v) {
			const auto& pos = curve.get(u, v).getPosition();
			const auto& normal = curve.get(u, v).getNormal();

			auto n = nodes.create(Point3d<float>(pos, normal));
			grid.set(u, v, n);
		}
	}

	const auto& cells = grid.toQuadCells();
	std::vector<TriangleCell> triangleCells;
	for (const auto& c : cells) {
		const auto& tCells = c.toTriangleCells();
		triangleCells.insert(triangleCells.end(), tCells.begin(), tCells.end());
	}

	for (const auto& t : triangleCells) {
		auto v1 = t.get()[0];
		auto v2 = t.get()[1];
		auto v3 = t.get()[2];
		createTriangleFace(v1, v2, v3);
	}
	return create(id);
}




Surface* SurfaceFactory::create(const CircularCurve3d<float>& curve, const int id)
{
	Node* centerNode = nodes.create(curve.getCenter());

	std::vector<Node*> createNodes;
	for (int i = 0; i < curve.getSize(); ++i) {
		Node* node = nodes.create(curve.get(i));
		createNodes.push_back(node);
	}
	for (int i = 0; i < createNodes.size() - 1; ++i) {
		auto v0 = centerNode;
		auto v1 = createNodes[i];
		auto v2 = createNodes[i + 1];
		createTriangleFace(v0, v1, v2);
	}
	return create(id);
}

Surface* SurfaceFactory::create(const TriangleCurve3d<float>& curve, const int id)
{
	std::vector< TriangleCell > cells;

	std::vector<std::vector<Node*>> createdNodes;
	for (int i = 0; i < curve.getSize(); ++i) {
		std::vector<Node*> ns;
		for (int j = 0; j <= i; ++j) {
			auto p = curve.get(i, j);
			Node* node = nodes.create(curve.get(i, j));
			ns.push_back(node);
		}
		createdNodes.push_back(ns);
	}

	for (int i = 1; i < createdNodes.size(); ++i) {
		for (int j = 0; j < i; ++j) {
			auto v0 = createdNodes[i - 1][j];
			auto v1 = createdNodes[i][j];
			auto v2 = createdNodes[i][j + 1];
			createTriangleFace(v0, v1, v2);
		}
	}
	for (int i = 1; i < createdNodes.size(); ++i) {
		for (int j = 0; j < i - 1; ++j) {
			auto v0 = createdNodes[i - 1][j];
			auto v1 = createdNodes[i][j + 1];
			auto v2 = createdNodes[i - 1][j + 1];
			createTriangleFace(v0, v1, v2);
		}
	}
	return create(id);
}

Surface* SurfaceFactory::create(const int id)
{
	auto s = new Surface(nodes.get(), edges.get(), faces.get(), id);
	return s;
}

Face* SurfaceFactory::createTriangleFace(Node* n1, Node* n2, Node* n3)
{
	auto e1 = edges.create(n1, n2);
	auto e2 = edges.create(n2, n3);
	auto e3 = edges.create(n3, n1);
	return faces.create(e1, e2, e3);
}

void SurfaceFactory::split(Face* f)
{
	const auto& es = f->getEdges();
	std::vector<Node*> startPoints;
	std::vector<Node*> midPoints;
	for (const auto& e : es) {
		startPoints.push_back(e->getStart());
		midPoints.push_back(nodes.create(e->getMidPoint()));
	}

	createTriangleFace(startPoints[0], midPoints[0], midPoints[2]);
	createTriangleFace(midPoints[0], startPoints[1], midPoints[1]);
	createTriangleFace(midPoints[1], startPoints[2], midPoints[2]);


	createTriangleFace(midPoints[0], midPoints[1], midPoints[2]);

}