#ifndef __CRYSTAL_POLYGON_MARCHING_CUBE_TABLE_H__
#define __CRYSTAL_POLYGON_MARCHING_CUBE_TABLE_H__

#include <bitset>
#include <array>
#include <vector>

namespace Crystal {
	namespace Polygon {

		// The lookup tables are from  http://paulbourke.net/geometry/polygonise/
class MarchingCubeTable
{
		public:
			void buildEdgeTable();

			void buildTriangleTable();

			std::array< std::bitset<12>, 256 > getEdgeTable() const { return edgeTable; }

			std::vector< std::array< int, 16 > > getTriangleTable() const { return triTable; }

		private:
			std::array< std::bitset<12>, 256 > edgeTable;

			std::vector< std::array< int, 16 > > triTable;
		};
	}
}

#endif