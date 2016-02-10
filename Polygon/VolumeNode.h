#ifndef __CRYSTAL_POLYGON_VOLUME_NODE_H__
#define __CRYSTAL_POLYGON_VOLUME_NODE_H__

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Polygon {

class Particle;

class VolumeNode
{
public:
	VolumeNode();

	VolumeNode(const Math::Vector3d<float>& p, const float& v);

	Math::Vector3d<float> getInterpolatedPosition(const float v, const VolumeNode& rhs) const;

	Particle toParticle(const float radius) const;

private:
	Math::Vector3d<float> pos;
	float value;
};

	}
}

#endif