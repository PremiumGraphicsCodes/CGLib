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
	sizeX(volume.getGrid().getSizeX()),
	sizeY(volume.getGrid().getSizeY()),
	sizeZ(volume.getGrid().getSizeZ()),
	threshold(threshold)
{
	
	grid.resize(sizeX);
	for (int i = 0; i < sizeX; ++i) {
		grid[i].resize(sizeY);
		for (int j = 0; j < sizeY; ++j) {
			grid[i][j].resize(sizeZ);
			for (int k = 0; k < sizeZ; ++k) {
				const auto& pos = volume.toCenterPosition(i,j,k);
				const auto value = volume.getGrid().get(i, j, k);
				grid[i][j][k] = MCCell(pos, value);
				nodes.push_back(MCNode(pos, value));
			}
		}
	}
	createEdges();

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

}

std::bitset<8> MCGrid::getBit(int x, int y, int z) const
{
	std::bitset<8> bit;

	const int x1 = x;
	const int y1 = y;
	const int z1 = z;
	const int x2 = x + 1;
	const int y2 = y + 1;
	const int z2 = z + 1;

	if (getValue(x1, y1, z1) < threshold) { bit.set(0); }
	if (getValue(x2, y1, z1) < threshold) { bit.set(1); }
	if (getValue(x2, y2, z1) < threshold) { bit.set(2); }
	if (getValue(x1, y2, z1) < threshold) { bit.set(3); }
	if (getValue(x1, y1, z2) < threshold) { bit.set(4); }
	if (getValue(x2, y1, z2) < threshold) { bit.set(5); }
	if (getValue(x2, y2, z2) < threshold) { bit.set(6); }
	if (getValue(x1, y2, z2) < threshold) { bit.set(7); }
	return bit;
}


void MCGrid::createEdges() {
	for (int i = 0; i < sizeX-1; ++i) {
		for (int j = 0; j < sizeY-1; ++j) {
			for (int k = 0; k < sizeZ-1; ++k) {
				if (isUnderThreshold(i, j, k) != isUnderThreshold(i + 1, j, k)) {
					const auto v = mesh.createVertex( getPosition( grid[i][j][k], grid[i+1][j][k] ) );
					grid[i][j][k].vertices[0] = v;
					//gridEdges.push_back()
				}
				if (isUnderThreshold(i, j, k) != isUnderThreshold(i, j + 1, k)) {
					const auto v = mesh.createVertex( getPosition( grid[i][j][k], grid[i][j + 1][k]) );
					//grid[i][j][k].edges[3] = edges.back();
					//grid[i][j][k].edges[1] = &edges.back();

				}
				if (isUnderThreshold(i, j, k) != isUnderThreshold(i, j, k + 1)) {
					mesh.createVertex( getPosition( grid[i][j][k], grid[i][j][k + 1]));
				}
				if (isUnderThreshold(i, j, k) != isUnderThreshold(i + 1, j + 1, k)) {
					mesh.createVertex( getPosition( grid[i][j][k], grid[i + 1][j + 1][k]));
				}
				if (isUnderThreshold(i, j, k) != isUnderThreshold(i, j + 1, k + 1)) {
					mesh.createVertex( getPosition( grid[i][j][k], grid[i][j + 1][k + 1]));
				}
				if (isUnderThreshold(i, j, k) != isUnderThreshold(i + 1, j + 1, k + 1)) {
					mesh.createVertex( getPosition( grid[i][j][k], grid[i + 1][j + 1][k + 1]));
				}

			}
		}
	}
}
