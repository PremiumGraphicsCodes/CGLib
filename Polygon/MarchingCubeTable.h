#ifndef __CRYSTAL_POLYGON_MARCHING_CUBE_TABLE_H__
#define __CRYSTAL_POLYGON_MARCHING_CUBE_TABLE_H__

#include <bitset>
#include <array>
#include <vector>

namespace Crystal {
	namespace Polygon {

// The lookup tables are from  http://paulbourke.net/geometry/polygonise/

struct ITriangle
{
	ITriangle() :
		ITriangle(-1, -1, -1)
	{}

	ITriangle(const int i1, const int i2, const int i3) :
		i1(i1),
		i2(i2),
		i3(i3)
	{}

	const int i1;
	const int i2;
	const int i3;
};

struct IFace
{
	IFace()
	{}

	IFace(const std::vector<ITriangle>& triangles) :
		triangles(triangles)
	{}

	IFace(const std::vector<int>& indices) {
		if (indices.size() >= 3) {
			triangles.push_back( ITriangle(indices[0], indices[1], indices[2]) );
		}
		if (indices.size() >= 6) {
			triangles.push_back(ITriangle(indices[3], indices[4], indices[5]));
		}
		if (indices.size() >= 9) {
			triangles.push_back(ITriangle(indices[6], indices[7], indices[8]));
		}
		if (indices.size() >= 12) {
			triangles.push_back(ITriangle(indices[9], indices[10], indices[11]));
		}
		if (indices.size() >= 15) {
			triangles.push_back(ITriangle(indices[12], indices[13], indices[14]));

		}

	}

	std::vector<ITriangle> triangles;
};

class MarchingCubeTable
{
public:
	MarchingCubeTable() {
		buildEdgeTable();
		buildTriangleTable();
	}

	void buildEdgeTable();

	void buildTriangleTable();

	std::array< std::bitset<12>, 256 > getEdgeTable() const { return edgeTable; }

	std::array<IFace, 256> getTriangleTable() const { return triTable; }

private:
	std::array< std::bitset<12>, 256 > edgeTable;
	std::array<IFace, 256> triTable;
};
	}
}

#endif