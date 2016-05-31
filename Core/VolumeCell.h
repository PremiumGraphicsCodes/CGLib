#ifndef __CRYSTAL_POLYGON_VOLUME_CELL_H__
#define __CRYSTAL_POLYGON_VOLUME_CELL_H__

#include "../Math/Space3d.h"

namespace Crystal {
	namespace Math {
		template<typename>
		class Triangle;
	}
	namespace Core {
class VolumeNode;

class VolumeCell
{
public:
	VolumeCell(const Math::Space3d<float>& space, const std::array< float, 8>& values);

	std::vector< Math::Triangle<float> > toTriangles(const float isolevel) const;


private:
	Math::Space3d<float> space;
	std::array< float, 8> values;

	std::array< VolumeNode, 8 > toPositionValues() const;

	int getCubeIndex(const float isolevel) const;

	std::array< Math::Vector3d<float>, 12 > getPositions(const int cubeindex, const float isolevel) const;

};
	}
}

#endif
