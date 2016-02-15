#ifndef __CRYSTAL_POLYGON_VOLUME_OBJECT_H__
#define __CRYSTAL_POLYGON_VOLUME_OBJECT_H__

#include "../Math/Vector3d.h"
#include "../Math/Space3d.h"
#include "../Math/Grid3d.h"

#include "VolumeNode.h"

namespace Crystal {
	namespace Math {
		template<typename>
		class Triangle;
	}
	namespace Polygon {

class PolygonObject;
class ParticleObject;
class VolumeCell;

class VolumeObject
{
public:
	VolumeObject(const Math::Space3d<float>& space, const Math::Grid3d<float>& grid) :
		space(space),
		grid(grid)
	{}

	std::vector<VolumeNode> toNodes() const;

	PolygonObject* toPolygonObject(const float isolevel) const;

	ParticleObject* toParticleObject() const;

private:
	const Math::Space3d<float> space;
	const Math::Grid3d<float> grid;

	std::vector< Math::Triangle<float> > toTriangles(const float isolevel) const;

	VolumeCell toCell(const Math::Index3d index) const;
};
	}
}

#endif