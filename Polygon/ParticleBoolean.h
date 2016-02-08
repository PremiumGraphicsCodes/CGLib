#ifndef __CRYSTAL_POLYGON_PARTICLE_BOOLEAN_H__
#define __CRYSTAL_POLYGON_PARTICLE_BOOLEAN_H__

#include "ParticleObject.h"

namespace Crystal {
	namespace Polygon {

class ParticleBoolean
{
public:
	//ParticleBoolean()
	ParticleObject* createUnion();

	ParticleObject* createSub();

	ParticleObject* createIntersection();

private:
	//ParticleObject* object1;
	//ParticleObject* object2;
};
	}
}

#endif