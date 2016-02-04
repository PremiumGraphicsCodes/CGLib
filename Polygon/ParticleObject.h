#ifndef __CRYSTAL_POLYGON_PARTICLE_OBJECT_H__
#define __CRYSTAL_POLYGON_PARTICLE_OBJECT_H__

#include "Vertex.h"

namespace Crystal {
	namespace Polygon {

class ParticleObject
{
public:
	ParticleObject()
	{}

	ParticleObject(const VectorIdCollection& positions) :
		positions(positions)
	{}


private:
	VectorIdCollection positions;
};
	}
}

#endif