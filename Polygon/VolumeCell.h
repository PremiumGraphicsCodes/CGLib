#ifndef __CRYSTAL_POLYGON_VOLUME_CELL_H__
#define __CRYSTAL_POLYGON_VOLUME_CELL_H__

#include "../Math/Space3d.h"

namespace Crystal {
	namespace Math {
		template<typename>
		class Triangle;
	}
	namespace Polygon {
class VolumeNode;

class VolumeCell
{
public:
	VolumeCell(const Math::Space3d<float>& space, const std::array< float, 8>& values) :
		space(space),
		values(values)
	{}

	Math::Space3d<float> getSpace() const { return space; }

	std::array< float, 8 > getValues() const { return values; }

	std::array< VolumeNode, 8 > toPositionValues() const;

	Math::Triangle<float> toTriangle() const;

private:
	Math::Space3d<float> space;
	std::array< float, 8> values;
};
	}
}

#endif
