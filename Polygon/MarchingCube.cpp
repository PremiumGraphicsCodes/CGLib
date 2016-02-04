#include "MarchingCube.h"

#include "Face.h"

#include "Vertex.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;

MCNode::MCNode() :
	pos(Vector3d<float>(0, 0, 0)),
	value(0)
{}

MCNode::MCNode(const Vector3d<float>& p, const float& v) :
	pos(p),
	value(v)
{}

Vector3d<float> MCNode::getInterpolatedPosition(const float v, const MCNode& rhs) const
{
	const float scale = static_cast<float> (v - this->value) / static_cast<float>(rhs.value - this->value);
	return this->pos + scale * (rhs.pos - this->pos);
}

namespace {
	Vector3d<float> getUnitLengths(const Space3d<float>& space, const Index3d res)
	{
		const auto x = space.getLengths().getX() / res[0];
		const auto y = space.getLengths().getY() / res[1];
		const auto z = space.getLengths().getZ() / res[2];
		return Vector3d<float>(x, y, z);
	}


	MCNode toNode(const Space3d<float>& space, const Grid3d<float>& grid, const Index3d index)
	{
		const auto& lengths = getUnitLengths(space, grid.getSizes());
		const auto& innerSpace = space.offset(lengths);

		const auto divx = grid.getSizeX() - 1;
		const auto divy = grid.getSizeY() - 1;
		const auto divz = grid.getSizeZ() - 1;

		const auto v = grid.toArray8(index[0], index[1], index[2]);
		const auto s = space.getSubSpace(index, divx, divy, divz);
		const auto& center = s.getCenter();

		return MCNode(center, grid.get(index.getX(), index.getY(), index.getZ()));
	}
}

std::vector<MCNode> MCVolume::toNodes() const
{
	std::vector<MCNode> nodes;
	for (int x = 0; x < grid.getSizeX(); ++x) {
		for (int y = 0; y < grid.getSizeY(); ++y) {
			for (int z = 0; z < grid.getSizeZ(); ++z) {
				nodes.push_back( toNode( space, grid, Index3d(x, y, z)) );
			}
		}
	}
	return nodes;
}


//MCVolume::toNodes()

std::array< MCNode, 8 > MCCell::toPositionValues() const
{
	std::array< MCNode, 8 > pvs;
	const auto& positions = space.toArray();
	for (size_t i = 0; i < 8; ++i) {
		pvs[i] = MCNode(positions[i], values[i]);
	}
	return pvs;
}

namespace {


	MCCell toCell( const Space3d<float>& space, const Grid3d<float>& grid, const Index3d index)
	{
		const auto& lengths = getUnitLengths(space, grid.getSizes());
		const auto& innerSpace = space.offset(lengths);

		const auto divx = grid.getSizeX() - 1;
		const auto divy = grid.getSizeY() - 1;
		const auto divz = grid.getSizeZ() - 1;

		const auto v = grid.toArray8(index[0], index[1], index[2]);
		const auto s = space.getSubSpace(index, divx, divy, divz);

		return MCCell(s, v);
	}
}


std::vector<Triangle<float> > MarchingCube::march(const Space3d<float>& space, const Grid3d<float>& grid, const float isolevel)
{
	std::vector<Triangle<float>> triangles;
	for (int x = 0; x < grid.getSizeX() - 1; ++x) {
		for (int y = 0; y < grid.getSizeY() - 1; ++y) {
			for (int z = 0; z < grid.getSizeZ() - 1; ++z) {
				if (grid.isBoundary(x, y, z, isolevel)) {
					const auto& cell = ::toCell(space, grid, Index3d{ x, y, z });
					const int cubeindex = getCubeIndex(cell.getValues(), isolevel);
					const auto& vertices = getPositions(cubeindex, cell, isolevel);
					const auto& triTable = table.getTriangleTable();
					for (int i = 0; triTable[cubeindex][i] != -1; i += 3) {
						const auto& v1 = vertices[triTable[cubeindex][i]];
						const auto& v2 = vertices[triTable[cubeindex][i + 1]];
						const auto& v3 = vertices[triTable[cubeindex][i + 2]];
						const Triangle<float> t(v1, v2, v3);
						triangles.emplace_back(t);
					}
				}
			}
		}
	}
	return triangles;
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

std::array< Vector3d<float>, 12 > MarchingCube::getPositions(const int cubeindex, const MCCell& cell, const float isolevel) const
{
	std::array< Vector3d<float>, 12 > vertices;
	const auto& pvs = cell.toPositionValues();
	const auto& edgeTable = table.getEdgeTable();
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