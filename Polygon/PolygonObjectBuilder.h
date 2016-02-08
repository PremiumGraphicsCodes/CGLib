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
	MCVolume toVolume(const ParticleObject& particles, const int hashTableSize);

private:
	float getPoly6Kernel(const float distance, const float effectLength);

};

	}
}

#endif