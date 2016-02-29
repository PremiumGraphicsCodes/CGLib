#ifndef __CRYSTAL_PHYSICS_CLOTH_H__
#define __CRYSTAL_PHYSICS_CLOTH_H__

#include "PhysicsObject.h"
#include "Spring.h"

namespace Crystal {
	namespace Physics {

class UVParticle
{
	UVParticle(const std::vector< std::vector< Particle*> >& particles);

};

class Cloth : PhysicsObject
{
public:
	struct Param {
		float springCoe;
		float damperCoe;
	};

	Cloth( const std::vector< std::vector< Particle*> >& particles );

	void coordinate();

private:
	std::vector<Spring> uSprings;
	std::vector<Spring> vSprings;
};
	}
}

#endif
