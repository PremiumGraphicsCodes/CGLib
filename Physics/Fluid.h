#ifndef __CRYSTAL_PHYSICS_FLUID_H__
#define __CRYSTAL_PHYSICS_FLUID_H__

#include "PhysicsObject.h"

namespace Crystal {
	namespace Math {
		template<typename T>
		class Vector3d;
	}
	namespace Physics {

class Fluid : public PhysicsObject
{
public:
	Fluid();

	Fluid(const Math::Box<float>& box, const float divideLength, const float restDensity, const SPHConstant& constant);

	Fluid(const std::vector<SPHParticle*>& particles);

	void addExternalForce(const Math::Vector3d<float>& force);

	//void forwardTime(const float timeStep);
};

	}
}

#endif