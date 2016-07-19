#include "stdafx.h"
#include "Vertex.h"
#include "VertexCollection.h"
#include "PolygonBuilder.h"
#include "ParticleObject.h"
#include "PolygonMesh.h"
#include "Volume.h"
#include "VolumeCell.h"
#include "NodeGrid.h"
#include "OctTree.h"

using namespace Crystal::Math;
using namespace Crystal::Core;

namespace {
	Crystal::Math::SPHKernel<float> kernel;
	float getPoly6Kernel(const float distance, const float effectLength) {
		return kernel.getPoly6Kernel(distance, effectLength);
	}
}


PolygonMesh* PolygonBuilder::build(int id)
{
	VertexCollection vc(vertices);
	vc.renumber();
	FaceCollection fc(faces);
	fc.renumber();
	return new PolygonMesh(vc.get(), fc.get(), id);
}

PolygonBuilder::PolygonBuilder(const Volume& volume, float isolevel)
{
	const auto& triangles = volume.toTriangles(isolevel);
	std::list<Vertex*> vertices;
	for (const auto& t : triangles) {
		auto v1 = new Vertex(t.getv0(), t.getNormal(), 0);
		auto v2 = new Vertex(t.getv1(), t.getNormal(), 0);
		auto v3 = new Vertex(t.getv2(), t.getNormal(), 0);
		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);
		createFace(v1, v2, v3);
	}
	VertexCollection vc(vertices);
	vc.sort();
	auto vv = vc.get();
	this->vertices = std::vector<Vertex*>(vv.begin(), vv.end());
}

PolygonBuilder::PolygonBuilder(const ParticleObject& particle, const float isolevel, const int levelOfDetail, const Space3d<float>& space)
{
	OctTree tree(space);
	const auto& particles = particle.getParticles();
	for (auto& p : particles) {
		tree.add(p);
	}
	std::vector<VolumeCell> cells;
	const auto& children = tree.createChildren(levelOfDetail);//Vector3d<float>(effectLength,effectLength,effectLength));
	for (const auto& c : children) {
		const auto& box = c.getBoundingBox();
		const auto& poss = box.toSpace().toArray();
		std::array<float, 8> values;
		values.fill(0.0f);
		for (int i = 0; i < 8; ++i) {
			for (const auto& particle : c.getParticles()) {
				const auto dist2 = poss[i].getDistanceSquared(particle->getPosition());
				const auto radiusSquared = particle->getBoundingRadius() * particle->getBoundingRadius();
				if (dist2 < radiusSquared) {
					//const auto value = kernel.getPoly6Kernel(std::sqrt(dist2), std::sqrt(radiusSquared)) * particle->getDensity();
					const auto diff = poss[i] - particle->getPosition();
					const auto& m = particle->getMatrix().getInverse(); //getScaled(1.0 / particle->getBoundingRadius());
																		//				const auto mm = Matrix3d<float>(1.0 / particle->getRadii().getX(), 0, 0, 0, 1.0 / particle->getRadii().getY(), 0, 0, 0, 1.0 / particle->getRadii().getZ());
					const auto value = kernel.getCubicSpline(diff, m) * particle->getDensity();
					values[i] += value;
				}
			}
		}
		VolumeCell cell(c.getBoundingBox().toSpace(), values);
		cells.emplace_back(cell);
	}
	std::vector<Triangle3d<float>> triangles;
	for (const auto& cell : cells) {
		const auto& ts = cell.toTriangles(isolevel);
		triangles.insert(triangles.end(), ts.begin(), ts.end());
	}
	std::list<Vertex*> vertices;
	for (const auto& t : triangles) {
		auto v1 = new Vertex(t.getv0(), t.getNormal(), 0);
		auto v2 = new Vertex(t.getv1(), t.getNormal(), 0);
		auto v3 = new Vertex(t.getv2(), t.getNormal(), 0);
		createFace(v1, v2, v3);
		vertices.push_back(v1);
		vertices.push_back(v2);
		vertices.push_back(v3);
		//factory.create(t.toCurve3d());
	}
	VertexCollection vc(vertices);
	//vc.sort();
	this->vertices = std::vector<Vertex*>(vc.begin(), vc.end());
	//newMesh->removeOverlappedVertices();
}


PolygonBuilder::PolygonBuilder(const Curve3d<float>& curve)
{
	NodeGrid1d grid(curve.getUNumber(), curve.getVNumber());
	for (int u = 0; u < curve.getUNumber(); ++u) {
		for (int v = 0; v < curve.getVNumber(); ++v) {
			const auto& pos = curve.get(u, v).getPosition();
			const auto& normal = curve.get(u, v).getNormal();
			auto n = new Vertex(pos, normal, -1);
			vertices.push_back(n);
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
		auto n0 = t.get()[0];
		auto n1 = t.get()[1];
		auto n2 = t.get()[2];
		createFace(n0, n1, n2);
	}
}

PolygonBuilder::PolygonBuilder(const CircularCurve3d<float>& curve)
{
	Vertex* centerNode = new Vertex(curve.getCenter().getPosition(), -1);

	for (int i = 0; i < curve.getSize(); ++i) {
		vertices.push_back(new Vertex(curve.get(i)));
	}
	for (int i = 0; i < vertices.size() - 1; ++i) {
		auto n0 = centerNode;
		auto n1 = vertices[i];
		auto n2 = vertices[i + 1];
		createFace(n0, n1, n2);
	}
	{
		auto n0 = centerNode;
		auto n1 = vertices.back();
		auto n2 = vertices.front();
		createFace(n0, n1, n2);

	}
	vertices.push_back(centerNode);

}

PolygonBuilder::PolygonBuilder(const TriangleCurve3d<float>& curve)
{
	std::vector< TriangleCell > cells;
	std::vector<std::vector<Vertex*>> createdNodes;

	for (int i = 0; i < curve.getSize(); ++i) {
		std::vector<Vertex*> ns;
		for (int j = 0; j <= i; ++j) {
			auto p = curve.get(i, j);
			auto node = new Vertex(curve.get(i, j));
			vertices.push_back(node);
			ns.push_back(node);
		}
		createdNodes.push_back(ns);
	}

	for (int i = 1; i < createdNodes.size(); ++i) {
		for (int j = 0; j < i; ++j) {
			auto n0 = createdNodes[i - 1][j];
			auto n1 = createdNodes[i][j];
			auto n2 = createdNodes[i][j + 1];
			createFace(n0, n1, n2);
			//createFaces.push_back(f);
		}
	}
	for (int i = 1; i < createdNodes.size(); ++i) {
		for (int j = 0; j < i - 1; ++j) {
			auto n0 = createdNodes[i - 1][j];
			auto n1 = createdNodes[i][j + 1];
			auto n2 = createdNodes[i - 1][j + 1];
			createFace(n0, n1, n2);
			//createFaces.push_back(f);
		}
	}
}

void PolygonBuilder::createFaces(const std::vector<Vertex*>& vertices)
{
	std::list< Face* > fs;
	auto origin = vertices[0];
	for (size_t i = 1; i < vertices.size() - 1; i++) {
		auto v1 = vertices[i];
		auto v2 = vertices[i + 1];
		Edge* e1 = new Edge(origin, v1);
		Edge* e2 = new Edge(v1, v2);
		Edge* e3 = new Edge(v2, origin);

		fs.push_back(new Face(e1, e2, e3));
		v1->addFace(fs.back());
		v2->addFace(fs.back());
	}
}

void PolygonBuilder::createFace(Vertex* v1, Vertex* v2, Vertex* v3)
{
	auto e1 = new Edge(v1, v2);
	auto e2 = new Edge(v2, v3);
	auto e3 = new Edge(v3, v1);
	edges.push_back(e1);
	edges.push_back(e2);
	edges.push_back(e3);
	auto f = new Face(e1, e2, e3);
	faces.push_back(f);
}