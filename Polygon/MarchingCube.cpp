#include "MarchingCube.h"

#include "../Math/PositionValue.h"
#include "../Math/Volume3d.h"
#include "../Math/VolumeCell3d.h"
#include "TriangleFace.h"

#include "Vertex.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;




void MCGrid::march(const Volume3d<float, float>& volume)
{	
	createNodes(volume);
	createEdges(volume);
	createFaces(volume);
}


void MCGrid::createNodes(const Volume3d<float, float>& volume)
{
	nodes.resize(volume.getGrid().getSizeX());
	for (int x = 0; x < volume.getGrid().getSizeX(); ++x) {
		nodes[x].resize(volume.getGrid().getSizeY());
		for (int y = 0; y < volume.getGrid().getSizeY(); ++y) {
			nodes[x][y].resize(volume.getGrid().getSizeZ());
			for (int z = 0; z < volume.getGrid().getSizeZ(); ++z) {
				const auto& pos = volume.toCenterPosition(x, y, z);
				const auto value = volume.getGrid().get(x, y, z);
				nodes[x][y][z] = new MCNode(pos, value);
			}
		}
	}
}

void MCGrid::createEdges(const Volume3d<float, float>& volume)
{
	for (int x = 0; x < volume.getGrid().getSizeX() - 1; ++x) {
		for (int y = 0; y < volume.getGrid().getSizeY() - 1; ++y) {
			for (int z = 0; z < volume.getGrid().getSizeZ() - 1; ++z) {
				if (nodes[x][y][z]->isUnderThreshold(threshold) != nodes[x + 1][y][z]->isUnderThreshold(threshold)) {
					edges.push_back(new MCEdge(nodes[x][y][z], nodes[x + 1][y][z]));
					nodes[x][y][z]->xplus = edges.back();
				}
				if (nodes[x][y][z]->isUnderThreshold(threshold) != nodes[x][y + 1][z]->isUnderThreshold(threshold)) {
					edges.push_back(new MCEdge(nodes[x][y][z], nodes[x][y + 1][z]));
					nodes[x][y][z]->yplus = edges.back();
				}
				if (nodes[x][y][z]->isUnderThreshold(threshold) != nodes[x][y][z + 1]->isUnderThreshold(threshold)) {
					edges.push_back(new MCEdge(nodes[x][z][z], nodes[x][y][z + 1]));
					nodes[x][y][z]->zplus = edges.back();
				}
			}
		}
	}

	for (auto e : edges) {
		e->createVertex(threshold, &mesh);
	}

}


void MCGrid::createFaces(const Volume3d<float, float>& volume)
{
	for (int x = 0; x < volume.getGrid().getSizeX() - 1; ++x) {
		for (int y = 0; y < volume.getGrid().getSizeY() - 1; ++y) {
			for (int z = 0; z < volume.getGrid().getSizeZ() - 1; ++z) {
				const std::array<MCNode*, 8> ns = {
					nodes[x][y][z],
					nodes[x + 1][y][z],
					nodes[x + 1][y + 1][z],
					nodes[x][y + 1][z],
					nodes[x][y][z + 1],
					nodes[x + 1][y][z + 1],
					nodes[x + 1][y + 1][z + 1],
					nodes[x][y][z + 1]
				};
				const std::array< MCEdge*, 12> es = {
					nodes[x][y][z]->xplus,
					nodes[x + 1][y][z]->yplus,
					nodes[x][y + 1][z]->xplus,
					nodes[x][y][z]->yplus,
					nodes[x][y][z + 1]->xplus,
					nodes[x + 1][y][z + 1]->yplus,
					nodes[x][y + 1][z + 1]->xplus,
					nodes[x][y][z + 1]->yplus,
					nodes[x][y][z]->zplus,
					nodes[x + 1][y][z]->zplus,
					nodes[x + 1][y + 1][z]->zplus,
					nodes[x][y + 1][z]->zplus
				};
				MCCell* cell = new MCCell(ns, es);
				cell->createFaces(mesh, threshold, table);
			}
		}
	}
}


void MCGrid::clear()
{
	for (int i = 0; i < nodes.size(); ++i) {
		for (int j = 0; j < nodes[i].size(); ++j) {
			for (int k = 0; k < nodes[j].size(); ++k) {
				delete nodes[i][j][k];
			}
		}
	}
	nodes.clear();

	for (auto e : edges) {
		delete e;
	}
	edges.clear();

	for (auto c : cells) {
		delete c;
	}
	cells.clear();

	mesh.clear();
}

MCGrid::~MCGrid()
{
	clear();
}

