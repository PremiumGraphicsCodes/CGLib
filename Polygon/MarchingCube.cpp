#include "MarchingCube.h"

#include "../Math/PositionValue.h"
#include "../Math/Volume3d.h"
#include "../Math/VolumeCell3d.h"
#include "TriangleFace.h"

#include "Vertex.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

void MarchingCube::march(const Volume3d<float, float>& volume, const float isolevel)
{
	const auto& grid = volume.getGrid();
	for (int x = 0; x < grid.getSizeX() - 1; ++x) {
		for (int y = 0; y < grid.getSizeY() - 1; ++y) {
			for (int z = 0; z < grid.getSizeZ() - 1; ++z) {
				if (grid.isBoundary(x, y, z, isolevel)) {
					VolumeCell3d<float, float> vc = volume.toCell(Index3d{ x, y, z });
					MCCell cell( vc.getSpace(), vc.getValues());
					build(cell, isolevel);
					//triangles.insert(triangles.end(), ts.begin(), ts.end());
				}
			}
		}
	}

}

void MarchingCube::build(const MCCell& cell, const float isolevel)
{
	std::vector<TriangleFace> triangles;
	MCCube cube(cell.getValues(), isolevel);
	const int cubeindex = cube.getBit().to_ulong();
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

MCCube::MCCube(const std::array< float, 8 >& val, const float isolevel)
{
	if (val[0] < isolevel) { bit.set(0); }
	if (val[1] < isolevel) { bit.set(1); }
	if (val[2] < isolevel) { bit.set(2); }
	if (val[3] < isolevel) { bit.set(3); }
	if (val[4] < isolevel) { bit.set(4); }
	if (val[5] < isolevel) { bit.set(5); }
	if (val[6] < isolevel) { bit.set(6); }
	if (val[7] < isolevel) { bit.set(7); }
}

std::vector< Vertex* > MarchingCube::createVertices(const int cubeindex, const MCCell& cell, const float isolevel)
{
	const auto& pvs = cell.toPositionValues();
	const auto& edgeTable = table.getEdgeTable();


	std::array<MCEdge,12> edges;
	if (edgeTable[cubeindex][0]) {
		edges[0] = MCEdge( pvs[0], pvs[1] );
	}
	if (edgeTable[cubeindex][1]) {
		edges[1] = MCEdge(pvs[1], pvs[2] );
	}
	if (edgeTable[cubeindex][2]) {
		edges[2] = MCEdge(pvs[2], pvs[3]);
	}
	if (edgeTable[cubeindex][3]) {
		edges[3] = (MCEdge(pvs[3], pvs[0]));
	}
	if (edgeTable[cubeindex][4]) {
		edges[4] =(MCEdge(pvs[4], pvs[5]));
	}
	if (edgeTable[cubeindex][5]) {
		edges[5] = (MCEdge(pvs[5], pvs[6]));
	}
	if (edgeTable[cubeindex][6]) {
		edges[6] =(MCEdge(pvs[6], pvs[7]));
	}
	if (edgeTable[cubeindex][7]) {
		edges[7] = (MCEdge(pvs[7], pvs[4]));
	}
	if (edgeTable[cubeindex][8]) {
		edges[8] = MCEdge(pvs[0], pvs[4]);
	}
	if (edgeTable[cubeindex][9]) {
		edges[9] = MCEdge(pvs[1], pvs[5]);
	}
	if (edgeTable[cubeindex][10]) {
		edges[10] = MCEdge(pvs[2], pvs[6]);
	}
	if (edgeTable[cubeindex][11]) {
		edges[11] = (MCEdge(pvs[3], pvs[7]));
	}

	std::vector< Vertex* > vertices;
	for (auto e : edges) {
		 vertices.push_back( mesh.createVertex( e.getInterpolatedPosition(isolevel)) );
	}

	return vertices;
}
