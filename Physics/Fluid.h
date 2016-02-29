#ifndef __CRYSTAL_PHYSICS_FLUID_H__
#define __CRYSTAL_PHYSICS_FLUID_H__

#include "PhysicsObject.h"

namespace Crystal {
	namespace Physics {

class Fluid : PhysicsObject
{
public:
	Fluid();

	void forwardTime(const float timeStep);
};

	}
}

#endif