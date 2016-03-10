#ifndef __CRYSTAL_PHYSICS_SPRING_H__
#define __CRYSTAL_PHYSICS_SPRING_H__

#include "SPHParticle.h"
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

	Spring(const SPHParticlePair& pair, const Param param);

	void coordinate(const float dt);

private:
	const SPHParticlePair& pair;
	Param param;
};
	}
}

#endif