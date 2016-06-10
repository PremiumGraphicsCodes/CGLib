#include "Surface.h"
#include "Edge.h"
#include "Node.h"
#include "Face.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

Surface::Surface()
{
	nextNodeId = 0;
	nextEdgeId = 0;
	nextFaceId = 0;

}

Surface::Surface(const Curve3d<float>& curve)
{
	nextNodeId = 0;
	nextEdgeId = 0;
	nextFaceId = 0;
	/*
	std::vector< std::vector< Node* > > nodeGrid(curve.getVNumber());
	for (int u = 0; u < curve.getUNumber(); ++u) {
		for (int v = 0; v < curve.getVNumber(); ++v) {
			Node* node = new Node(nextNodeId++);
			nodeGrid[u][v] = node;
		}
	}
	*/
	add(curve);
}

#include "../Util/Array2d.h"

void Surface::add(const Curve3d<float>& curve)
{
	Array2d<Node*> grid(curve.getUNumber(), curve.getVNumber());
	//NodeGrid2d grid(curve.getUNumber(), curve.getVNumber());
	for (int u = 0; u < curve.getUNumber(); ++u) {
		for (int v = 0; v < curve.getVNumber(); ++v) {
			const auto& pos = curve.get(u, v).getPosition();
			const auto& normal = curve.get(u, v).getNormal();

			Node* node = new Node(pos, normal, nextNodeId++);
			nodes.push_back(node);
			grid.set(u, v, node);
		}
	}

	for (int u = 0; u < curve.getUNumber() - 1; ++u) {
		for (int v = 0; v < curve.getVNumber() - 1; ++v) {
			auto v1 = grid.get(u, v);
			auto v2 = grid.get(u + 1, v);
			auto v3 = grid.get(u + 1, v + 1);
			auto v4 = grid.get(u, v + 1);

			Edge* e1 = new Edge(v1, v2, nextEdgeId++);
			Edge* e2 = new Edge(v2, v3, nextEdgeId++);
			Edge* e3 = new Edge(v3, v1, nextEdgeId++);

			Face* f1 = new Face({ e1, e2, e3 }, nextFaceId++);

			Edge* e4 = new Edge(v1, v3, nextEdgeId++);
			Edge* e5 = new Edge(v3, v4, nextEdgeId++);
			Edge* e6 = new Edge(v4, v1, nextEdgeId++);

			Face* f2 = new Face({ e4, e5, e6 }, nextFaceId++);

			edges.push_back(e1);
			edges.push_back(e2);
			edges.push_back(e3);
			edges.push_back(e4);
			edges.push_back(e5);
			edges.push_back(e6);

			faces.push_back(f1);
			faces.push_back(f2);
		}
	}

}

void Surface::add(const CircularCurve3d<float>& curve)
{
	const auto center = curve.getCenter();
	Node* centerNode = new Node(center.getPosition(), center.getNormal(), nextNodeId++);
	nodes.push_back(centerNode);

	for (int i = 0; i < curve.getSize(); ++i) {
		const auto& pos = curve.get(i).getPosition();
		const auto& normal = curve.get(i).getNormal();

		Node* node = new Node(pos, normal, nextNodeId++);
		nodes.push_back(node);
	}
	for (int i = 0; i < nodes.size()-2; ++i) {
		auto v0 = centerNode;
		auto v1 = nodes[i];
		auto v2 = nodes[i + 1];
		Edge* e1 = new Edge(v0, v1, nextEdgeId++);
		Edge* e2 = new Edge(v1, v2, nextEdgeId++);
		Edge* e3 = new Edge(v2, v0, nextEdgeId++);
		Face* f1 = new Face({ e1, e2, e3 }, nextFaceId++);
		edges.push_back(e1);
		edges.push_back(e2);
		edges.push_back(e3);
		faces.push_back(f1);
	}
}



Surface::~Surface()
{
	clear();
}

void Surface::clear()
{
	for (auto f : faces) {
		delete f;
	}
	faces.clear();
	for (auto e : edges) {
		delete e;
	}
	edges.clear();
	for (auto n : nodes) {
		delete n;
	}
	nodes.clear();
}

std::vector<unsigned int> Surface::toIndices() const
{
	std::vector<unsigned int> indices;
	for (auto f : faces) {
		const auto& edges = f->getEdges();
		for (auto e : edges) {
			indices.push_back( e->getStart()->getId() );
		}
		//indices.push_back( edges.back()->getEnd()->getId() );
	}
	return indices;
}
