#include "MarchingCube.h"

#include "../Math/PositionValue.h"
#include "../Math/Volume3d.h"
#include "../Math/VolumeCell3d.h"
#include "TriangleFace.h"

#include "Vertex.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;



MCGrid::MCGrid(const Volume3d<float, float>& volume, const float threshold) :
	threshold(threshold)
{	
	nodes.resize(volume.getGrid().getSizeX());
	for (int i = 0; i < volume.getGrid().getSizeX(); ++i) {
		nodes[i].resize(volume.getGrid().getSizeY());
		for (int j = 0; j < volume.getGrid().getSizeY(); ++j) {
			nodes[i][j].resize(volume.getGrid().getSizeZ());
			for (int k = 0; k < volume.getGrid().getSizeZ(); ++k) {
				const auto& pos = volume.toCenterPosition(i,j,k);
				const auto value = volume.getGrid().get(i, j, k);
				nodes[i][j][k] = new MCNode(pos, value);
			}
		}
	}

	for (int i = 0; i < volume.getGrid().getSizeX()-1; ++i) {
		for (int j = 0; j < volume.getGrid().getSizeY()-1; ++j) {
			for (int k = 0; k < volume.getGrid().getSizeZ()-1; ++k) {

				if(nodes[i][j][k]->isUnderThreshold(threshold) != nodes[i+1][j][k]->isUnderThreshold(threshold) ) {
					edges.push_back(new MCEdge(nodes[i][j][k], nodes[i + 1][j][k]));
					nodes[i][j][k]->xplus = edges.back();
				}
				if (nodes[i][j][k]->isUnderThreshold(threshold) != nodes[i][j + 1][k]->isUnderThreshold(threshold)) {
					edges.push_back(new MCEdge(nodes[i][j][k], nodes[i][j + 1][k]));
					nodes[i][j][k]->yplus = edges.back();
				}
				if (nodes[i][j][k]->isUnderThreshold(threshold) != nodes[i][j][k + 1]->isUnderThreshold(threshold)) {
					edges.push_back(new MCEdge(nodes[i][k][k], nodes[i][j][k + 1]));
					nodes[i][j][k]->zplus = edges.back();
				}
			}
		}
	}

	for (auto e : edges) {
		mesh.addVertex( e->createVertex(threshold) );
	}

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
					nodes[x+1][y][z]->yplus,
					nodes[x][y+1][z]->xplus,
					nodes[x][y][z]->yplus,
					nodes[x][y][z+1]->xplus,
					nodes[x+1][y][z+1]->yplus,
					nodes[x][y+1][z+1]->xplus,
					nodes[x][y][z+1]->yplus,
					nodes[x][y][z]->zplus,
					nodes[x+1][y][z]->zplus,
					nodes[x+1][y+1][z]->zplus,
					nodes[x][y+1][z]->zplus
				};
				MCCell* cell = new MCCell(ns, es);
				const auto bit = cell->getBit(threshold);
				const auto& triTable = table.getTriangleTable();
				const auto& table = triTable[bit.to_ulong()];

				for (auto t : table.triangles) {
					auto e1 = es[t.i1]->v;
					auto e2 = es[t.i2]->v;
					auto e3 = es[t.i3]->v;
					mesh.createFace( e1, e2, e3);
				}

			}
		}
	}
}

MCGrid::~MCGrid()
{
	for (int i = 0; i < nodes.size(); ++i) {
		for (int j = 0; j < nodes[i].size(); ++j) {
			for (int k = 0; k < nodes[j].size(); ++k) {
				delete nodes[i][j][k];
			}
		}
	}


	for (auto e : edges) {
		delete e;
	}

	for (auto c : cells) {
		delete c;
	}
}

