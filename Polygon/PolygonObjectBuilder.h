#ifndef __CRYSTAL_POLYGON_POLYGON_OBJECT_BUILDER_H__
#define __CRYSTAL_POLYGON_POLYGON_OBJECT_BUILDER_H__

#include "ParticleObject.h"
#include "PolygonObject.h"

#include "MarchingCube.h"

namespace Crystal {
	namespace Polygon {

class PolygonObjectBuilder
{
public:
	MCVolume toVolume(const ParticleObject& particles, const Math::Index3d resolution, const int hashTableSize);

private:
	float getPoly6Kernel(const float distance, const float effectLength) {
		const auto poly6Constant = 315.0f / (64.0f * Math::Tolerance<float>::getPI() * pow(effectLength, 9));
		return poly6Constant * pow(effectLength * effectLength - distance * distance, 3);
	}

};

	}
}

#endif