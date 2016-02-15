#include "MarchingCube.h"

#include "Face.h"

#include "Vertex.h"
#include "VolumeCell.h"

using namespace Crystal::Math;
using namespace Crystal::Polygon;


//MCVolume::toNodes()


namespace {
	Vector3d<float> getUnitLengths(const Space3d<float>& space, const Index3d res)
	{
		const auto x = space.getLengths().getX() / res[0];
		const auto y = space.getLengths().getY() / res[1];
		const auto z = space.getLengths().getZ() / res[2];
		return Vector3d<float>(x, y, z);
	}


	VolumeCell toCell(const Space3d<float>& space, const Grid3d<float>& grid, const Index3d index)
	{
		const auto& lengths = getUnitLengths(space, grid.getSizes());
		const auto& innerSpace = space.offset(lengths);

		const auto divx = grid.getSizeX() - 1;
		const auto divy = grid.getSizeY() - 1;
		const auto divz = grid.getSizeZ() - 1;

		const auto v = grid.toArray8(index[0], index[1], index[2]);
		const auto s = space.getSubSpace(index, divx, divy, divz);

		return VolumeCell(s, v);
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
					const auto& ts = cell.toTriangles(isolevel);
					triangles.insert(triangles.end(), ts.begin(), ts.end());
					/*
					const auto cubeindex = cell.getCubeIndex(isolevel);
					const auto& vertices = cell.getPositions(cubeindex, isolevel);
					const auto& triTable = table.getTriangleTable();
					for (int i = 0; triTable[cubeindex][i] != -1; i += 3) {
						const auto& v1 = vertices[triTable[cubeindex][i]];
						const auto& v2 = vertices[triTable[cubeindex][i + 1]];
						const auto& v3 = vertices[triTable[cubeindex][i + 2]];
						const Triangle<float> t(v1, v2, v3);
						triangles.emplace_back(t);
					}
					*/
				}
			}
		}
	}
	return triangles;
}

std::vector< Triangle<float> > MarchingCube::march(const VolumeObject& volume, const float isolevel)
{
	return march(volume.getSpace(), volume.getGrid(), isolevel);
}


