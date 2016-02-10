#ifndef __CRYSTAL_POLYGON_VOLUME_OBJECT_H__
#define __CRYSTAL_POLYGON_VOLUME_OBJECT_H__

#include "../Math/Vector3d.h"
#include "../Math/Space3d.h"
#include "../Math/Grid3d.h"

namespace Crystal {
	namespace Polygon {

class PolygonObject;

class VolumeNode
{
public:
	VolumeNode();

	VolumeNode(const Math::Vector3d<float>& p, const float& v);

	Math::Vector3d<float> getInterpolatedPosition(const float v, const VolumeNode& rhs) const;

private:
	Math::Vector3d<float> pos;
	float value;
};

class MCCell
{
public:
	MCCell(const Math::Space3d<float>& space, const std::array< float, 8>& values) :
		space(space),
		values(values)
	{}

	Math::Space3d<float> getSpace() const { return space; }

	std::array< float, 8 > getValues() const { return values; }

	std::array< VolumeNode, 8 > toPositionValues() const;

private:
	Math::Space3d<float> space;
	std::array< float, 8> values;
};


class VolumeObject
{
public:
	VolumeObject(const Math::Space3d<float>& space, const Math::Grid3d<float>& grid) :
		space(space),
		grid(grid)
	{}

	std::vector<VolumeNode> toNodes() const;

	Math::Space3d<float> getSpace() const { return space; }

	Math::Grid3d<float> getGrid() const { return grid; }

	PolygonObject* toPolygonObject(const float isolevel) const;

private:
	const Math::Space3d<float> space;
	const Math::Grid3d<float> grid;
};
	}
}

#endif