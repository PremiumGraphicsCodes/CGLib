#include "stdafx.h"
#include "VolumeCell.h"
#include "VolumeNode.h"

#include "../Math/Triangle.h"
#include "MarchingCubeTable.h"


#include <bitset>

using namespace Crystal::Math;
using namespace Crystal::Core;

VolumeCell::VolumeCell(const Space3d<float>& space, const std::array< float, 8>& values) :
	space(space),
	values(values)
{}


int VolumeCell::getCubeIndex(const float isolevel) const
{
	std::bitset<8> bit;
	if (values[0] < isolevel) { bit.set(0); }
	if (values[1] < isolevel) { bit.set(1); }
	if (values[2] < isolevel) { bit.set(2); }
	if (values[3] < isolevel) { bit.set(3); }
	if (values[4] < isolevel) { bit.set(4); }
	if (values[5] < isolevel) { bit.set(5); }
	if (values[6] < isolevel) { bit.set(6); }
	if (values[7] < isolevel) { bit.set(7); }
	return static_cast<int>(bit.to_ulong());
}


std::vector< Triangle<float> > VolumeCell::toTriangles(const float isolevel) const
{
	MarchingCubeTable* table = MarchingCubeTable::getInstance();

	std::vector<Triangle<float>> triangles;

	const auto cubeIndex = getCubeIndex(isolevel);
	const auto& vertices = getPositions(cubeIndex, isolevel);
	const auto& triTable = table->getTriangleTable();
	for (int i = 0; triTable[cubeIndex][i] != -1; i += 3) {
		const auto& v1 = vertices[triTable[cubeIndex][i]];
		const auto& v2 = vertices[triTable[cubeIndex][i + 1]];
		const auto& v3 = vertices[triTable[cubeIndex][i + 2]];
		const Triangle<float> t(v1, v2, v3);
		triangles.emplace_back(t);
	}

	return triangles;
}

std::array< VolumeNode, 8 > VolumeCell::toPositionValues() const
{
	std::array< VolumeNode, 8 > pvs;
	const auto& positions = space.toArray();
	for (size_t i = 0; i < 8; ++i) {
		pvs[i] = VolumeNode(positions[i], values[i]);
	}
	return pvs;
}


std::array< Vector3d<float>, 12 > VolumeCell::getPositions(const int cubeindex, const float isolevel) const
{
	MarchingCubeTable* table = MarchingCubeTable::getInstance();

	std::array< Vector3d<float>, 12 > vertices;
	const auto& pvs = toPositionValues();
	const auto& edgeTable = table->getEdgeTable();
	if (edgeTable[cubeindex][0]) {
		vertices[0] = pvs[0].getInterpolatedPosition(isolevel, pvs[1]); // interpolate(isolevel, p[0], p[1], val[0], val[1]);
	}
	if (edgeTable[cubeindex][1]) {
		vertices[1] = pvs[1].getInterpolatedPosition(isolevel, pvs[2]);
	}
	if (edgeTable[cubeindex][2]) {
		vertices[2] = pvs[2].getInterpolatedPosition(isolevel, pvs[3]);
	}
	if (edgeTable[cubeindex][3]) {
		vertices[3] = pvs[3].getInterpolatedPosition(isolevel, pvs[0]);
	}
	if (edgeTable[cubeindex][4]) {
		vertices[4] = pvs[4].getInterpolatedPosition(isolevel, pvs[5]);
	}
	if (edgeTable[cubeindex][5]) {
		vertices[5] = pvs[5].getInterpolatedPosition(isolevel, pvs[6]);
	}
	if (edgeTable[cubeindex][6]) {
		vertices[6] = pvs[6].getInterpolatedPosition(isolevel, pvs[7]);
	}
	if (edgeTable[cubeindex][7]) {
		vertices[7] = pvs[7].getInterpolatedPosition(isolevel, pvs[4]);
	}
	if (edgeTable[cubeindex][8]) {
		vertices[8] = pvs[0].getInterpolatedPosition(isolevel, pvs[4]);
	}
	if (edgeTable[cubeindex][9]) {
		vertices[9] = pvs[1].getInterpolatedPosition(isolevel, pvs[5]);
	}
	if (edgeTable[cubeindex][10]) {
		vertices[10] = pvs[2].getInterpolatedPosition(isolevel, pvs[6]);
	}
	if (edgeTable[cubeindex][11]) {
		vertices[11] = pvs[3].getInterpolatedPosition(isolevel, pvs[7]);
	}
	return vertices;
}