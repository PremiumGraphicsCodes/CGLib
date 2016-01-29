#include "MarchingCube.h"

#include "../Math/PositionValue.h"
#include "../Math/Volume3d.h"
#include "../Math/VolumeCell3d.h"
#include "TriangleFace.h"

#include "Vertex.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

/*
void MarchingCube::march(const Volume3d<float, float>& volume, const float isolevel)
{
	std::vector< Index3d > boundaryIndices;
	const auto& grid = volume.getGrid();
	MCGrid mcGrid(grid.getSizeX(), grid.getSizeY(), grid.getSizeZ());
	for (int x = 0; x < grid.getSizeX() - 1; ++x) {
		for (int y = 0; y < grid.getSizeY() - 1; ++y) {
			for (int z = 0; z < grid.getSizeZ() - 1; ++z) {
				const auto& pos = volume.toCenterPosition(x, y, z);
				const auto v = grid.get(x, y, z);
				mcGrid.set(x, y, z, pos, v);

			}
		}
	}

}

void MarchingCube::build(const MCCell& cell, const float isolevel)
{
	std::vector<TriangleFace> triangles;
	const int cubeindex = cell.getBit(isolevel).to_ulong();
	const auto& vertices = createVertices(cubeindex, cell, isolevel);

	const auto& triTable = table.getTriangleTable();
	const auto& table = triTable[cubeindex];
	for (auto t : table.triangles) {
		const auto v1 = vertices[t.i1];
		const auto v2 = vertices[t.i2];
		const auto v3 = vertices[t.i3];
		mesh.createFace( v1, v2, v3 );
	}
}
*/

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
					nodes[i+1][j][k]->xminus = edges.back();
				}
				if (nodes[i][j][k]->isUnderThreshold(threshold) != nodes[i][j + 1][k]->isUnderThreshold(threshold)) {
					edges.push_back(new MCEdge(nodes[i][j][k], nodes[i][j + 1][k]));
					nodes[i][j][k]->yplus = edges.back();
					nodes[i][j+1][k]->yminus = edges.back();
				}
				if (nodes[i][j][k]->isUnderThreshold(threshold) != nodes[i][j][k + 1]->isUnderThreshold(threshold)) {
					edges.push_back(new MCEdge(nodes[i][k][k], nodes[i][j][k + 1]));
					nodes[i][j][k]->zplus = edges.back();
					nodes[i][j][k+1]->zminus = edges.back();

				}
			}
		}
	}

	for (auto e : edges) {
		mesh.createVertex( e->getPosition(threshold) );
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
					nodes[x+1][y+1][z]->xminus,
					nodes[x][y+1][z]->yminus,
					nodes[x][y][z+1]->xplus,
					nodes[x+1][y][z+1]->yplus,
					nodes[x+1][y+1][z+1]->xminus,
					nodes[x][y+1][z+1]->yminus,
					nodes[x][y][z]->zplus,
					nodes[x+1][y][z]->zplus,
					nodes[x+1][y+1][z]->zplus,
					nodes[x][y+1][z]->zplus
				};
				MCCell* cell = new MCCell(ns, es);
				const auto bit = cell->getBit(threshold);
				const auto& triTable = table.getTriangleTable();
				const auto& table = triTable[bit.to_ulong()];

				cell->getActiveEdges();
			}
		}
	}


	/*
	for (int i = 0; i < sizeX-1; ++i) {
		for (int j = 0; j < sizeY-1; ++j) {
			for (int k = 0; k < sizeZ-1; ++k) {
				const int cubeIndex = getBit(i, j, k).to_ulong();
				const auto& triTable = table.getTriangleTable();
				const auto& table = triTable[cubeIndex];
				const auto& vertices = grid[i][j][k].vertices;

				for (auto t : table.triangles) {
					auto e1 = vertices[t.i1];
					auto e2 = vertices[t.i2];
					//const auto v1 = vertices[t.i1];
					//const auto v2 = vertices[t.i2];
					//const auto v3 = vertices[t.i3];
					//mesh.createFace(v1, v2, v3);
				}
			}
		}
	}
	*/

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

