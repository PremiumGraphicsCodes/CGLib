#ifndef __CRYSTAL_POLYGON_VOLUME_OBJECT_H__
#define __CRYSTAL_POLYGON_VOLUME_OBJECT_H__

#include "../Math/Vector3d.h"
#include "../Math/Space3d.h"
#include "../Math/Grid3d.h"

#include "VolumeNode.h"

namespace Crystal {
	namespace Polygon {

class PolygonObject;
class ParticleObject;




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

	ParticleObject* toParticleObject() const;

private:
	const Math::Space3d<float> space;
	const Math::Grid3d<float> grid;
};
	}
}

#endif