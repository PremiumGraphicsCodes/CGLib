#ifndef __CRYSTAL_PHYSICS_SPRING_H__
#define __CRYSTAL_PHYSICS_SPRING_H__

#include "Particle.h"
#include "ParticlePair.h"

namespace Crystal {
	namespace Physics {

class Spring
{
public:
	struct Param {
		float springCoe;
		float damperCoe;
		float restDistance;
	};

	Spring(const ParticlePair& pair, const Param param);

	void coordinate(const float dt);

private:
	const ParticlePair& pair;
	Param param;
};
	}
}

#endif