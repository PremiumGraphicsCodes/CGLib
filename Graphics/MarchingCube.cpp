#include "MarchingCube.h"

#include "../Math/PositionValue.h"
#include "../Math/Volume3d.h"
#include "../Math/VolumeCell3d.h"

#include "PolygonReduction.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics::Experiment;

void MarchingCube::march(const Volume3d<float, float>& volume, const float isolevel) const
{
	const auto& grid = volume.getGrid();
	//std::vector<Triangle<GeomType>> triangles;
	for (int x = 0; x < grid.getSizeX() - 1; ++x) {
		for (int y = 0; y < grid.getSizeY() - 1; ++y) {
			for (int z = 0; z < grid.getSizeZ() - 1; ++z) {
				if (grid.isBoundary(x, y, z, isolevel)) {
					const auto& cell = volume.toCell(Index3d{ x, y, z });
					//const auto& ts = build(cell, isolevel);
					//triangles.insert(triangles.end(), ts.begin(), ts.end());
				}
			}
		}
	}

}

std::vector<TriangleFace> MarchingCube::build(const VolumeCell3d<float, float>& cell, const float isolevel)
{
	std::vector<TriangleFace> triangles;
	const int cubeindex = getCubeIndex(cell.getValues(), isolevel);
	const auto& vertices = getPositions(cubeindex, cell, isolevel);
	return std::move(build(cubeindex, vertices));
}

std::vector<TriangleFace> MarchingCube::build(const int cubeindex, const std::array<std::shared_ptr<Vertex>, 12>& vertices)
{
	std::vector<TriangleFace> triangles;
	const auto& triTable = table.getTriangleTable();
	for (int i = 0; triTable[cubeindex][i] != -1; i += 3) {
		const auto v1 = vertices[triTable[cubeindex][i]];
		const auto v2 = vertices[triTable[cubeindex][i + 1]];
		const auto v3 = vertices[triTable[cubeindex][i + 2]];
		TriangleFace t({ v1, v2, v3 });
		triangles.emplace_back(t);
	}

	return std::move(triangles);
}

int MarchingCube::getCubeIndex(const std::array< float, 8 >& val, const float isolevel) const
{
	std::bitset<8> bit;
	if (val[0] < isolevel) { bit.set(0); }
	if (val[1] < isolevel) { bit.set(1); }
	if (val[2] < isolevel) { bit.set(2); }
	if (val[3] < isolevel) { bit.set(3); }
	if (val[4] < isolevel) { bit.set(4); }
	if (val[5] < isolevel) { bit.set(5); }
	if (val[6] < isolevel) { bit.set(6); }
	if (val[7] < isolevel) { bit.set(7); }
	return static_cast<int>(bit.to_ulong());
}

std::array< std::shared_ptr<Vertex>, 12 > MarchingCube::getPositions(const int cubeindex, const VolumeCell3d<float, float>& cell, const float isolevel)
{
	std::array< std::shared_ptr<Vertex>, 12 > vertices;
	const auto& pvs = cell.toPositionValues();
	const auto& edgeTable = table.getEdgeTable();
	if (edgeTable[cubeindex][0]) {
		vertices[0] = mesh.createVertex( pvs[0].getInterpolatedPosition(isolevel, pvs[1]) ); // interpolate(isolevel, p[0], p[1], val[0], val[1]);
	}
	if (edgeTable[cubeindex][1]) {
		vertices[1] = mesh.createVertex( pvs[1].getInterpolatedPosition(isolevel, pvs[2]) );
	}
	if (edgeTable[cubeindex][2]) {
		vertices[2] = mesh.createVertex(pvs[2].getInterpolatedPosition(isolevel, pvs[3]) );
	}
	if (edgeTable[cubeindex][3]) {
		vertices[3] = mesh.createVertex(pvs[3].getInterpolatedPosition(isolevel, pvs[0]));
	}
	if (edgeTable[cubeindex][4]) {
		vertices[4] = mesh.createVertex(pvs[4].getInterpolatedPosition(isolevel, pvs[5]));
	}
	if (edgeTable[cubeindex][5]) {
		vertices[5] = mesh.createVertex(pvs[5].getInterpolatedPosition(isolevel, pvs[6]));
	}
	if (edgeTable[cubeindex][6]) {
		vertices[6] = mesh.createVertex(pvs[6].getInterpolatedPosition(isolevel, pvs[7]));
	}
	if (edgeTable[cubeindex][7]) {
		vertices[7] = mesh.createVertex(pvs[7].getInterpolatedPosition(isolevel, pvs[4]));
	}
	if (edgeTable[cubeindex][8]) {
		vertices[8] = mesh.createVertex(pvs[0].getInterpolatedPosition(isolevel, pvs[4]));
	}
	if (edgeTable[cubeindex][9]) {
		vertices[9] = mesh.createVertex(pvs[1].getInterpolatedPosition(isolevel, pvs[5]));
	}
	if (edgeTable[cubeindex][10]) {
		vertices[10] = mesh.createVertex(pvs[2].getInterpolatedPosition(isolevel, pvs[6]));
	}
	if (edgeTable[cubeindex][11]) {
		vertices[11] = mesh.createVertex(pvs[3].getInterpolatedPosition(isolevel, pvs[7]));
	}
	return vertices;
}
