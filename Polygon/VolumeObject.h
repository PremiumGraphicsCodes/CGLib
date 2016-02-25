#ifndef __CRYSTAL_POLYGON_VOLUME_OBJECT_H__
#define __CRYSTAL_POLYGON_VOLUME_OBJECT_H__

#include "../Math/Vector3d.h"
#include "../Math/Space3d.h"
#include "../Math/Grid3d.h"

namespace Crystal {
	namespace Math {
		template<typename>
		class Triangle;
	}
	namespace Polygon {

class Particle;
class PolygonObject;
class ParticleObject;
class VolumeCell;
class VolumeNode;

class VolumeObject
{
public:
	VolumeObject(const Math::Space3d<float>& space, const Math::Grid3d<float>& grid) :
		space(space),
		grid(grid)
	{}

	VolumeNode toNode(const Math::Index3d index) const;

	std::vector<VolumeNode> toNodes() const;

	PolygonObject* toPolygonObject(const float isolevel) const;

	Math::Vector3d<float> getUnitLength() const;

	Math::Vector3d<float> toPosition(const Math::Index3d index) const;

	Particle toParticle(const Math::Index3d index, const float radius) const;

	ParticleObject* toParticleObject(const float radius,const float isolevel) const;

private:
	const Math::Space3d<float> space;
	const Math::Grid3d<float> grid;

	std::vector< Math::Triangle<float> > toTriangles(const float isolevel) const;

	VolumeCell toCell(const Math::Index3d index) const;
};
	}
}

#endif