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

void MCGrid::createEdges() {
	for (int i = 0; i < sizeX; ++i) {
		for (int j = 0; j < sizeY; ++j) {
			for (int k = 0; k < sizeZ; ++k) {
				if (isUnderThreshold(i, j, k) != isUnderThreshold(i + 1, j, k)) {
					edges.push_back(MCEdge(grid[i][j][k], grid[i + 1][j][k]));
					//gridEdges.push_back()
				}
				if (isUnderThreshold(i, j, k) != isUnderThreshold(i, j + 1, k)) {
					edges.push_back(MCEdge(grid[i][j][k], grid[i][j + 1][k]));
				}
				if (isUnderThreshold(i, j, k) != isUnderThreshold(i, j, k + 1)) {
					edges.push_back(MCEdge(grid[i][j][k], grid[i][j][k + 1]));
				}
				if (isUnderThreshold(i, j, k) != isUnderThreshold(i + 1, j + 1, k)) {
					edges.push_back(MCEdge(grid[i][j][k], grid[i + 1][j + 1][k]));
				}
				if (isUnderThreshold(i, j, k) != isUnderThreshold(i, j + 1, k + 1)) {
					edges.push_back(MCEdge(grid[i][j][k], grid[i][j + 1][k + 1]));
				}
				if (isUnderThreshold(i, j, k) != isUnderThreshold(i + 1, j + 1, k + 1)) {
					edges.push_back(MCEdge(grid[i][j][k], grid[i + 1][j + 1][k + 1]));
				}

			}
		}
	}
}

std::vector< Vector3d<float> > MCGrid::createVertices(float isolevel)
{
	std::vector< Vector3d<float> > vertices;
	for (const auto& e : edges) {
		 vertices.push_back( e.getInterpolatedPosition(isolevel) );
	}
	return vertices;
}
