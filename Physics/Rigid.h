#ifndef __CRYSTAL_PHYSICS_RIGID_H__
#define __CRYSTAL_PHYSICS_RIGID_H__

#include "PhysicsObject.h"

namespace Crystal {
	namespace Physics {

class Rigid : public PhysicsObject
{
public:
	Rigid();

	Rigid(const std::vector<Particle*>& particles);

	void coordinate(const float timeStep) override;

private:
	void getAngleVelosity(const Math::Vector3d<float>& I, const Math::Vector3d<float>& N, const float proceedTime);
	Math::Vector3d<float> angleVelosity;

	float getAngleAccelerationX(float x1, float x2, float x3, const Math::Vector3d<float>& I, const Math::Vector3d<float>& N);

	float getAngleAccelerationY(float x1, float x2, float x3, const Math::Vector3d<float>& I, const Math::Vector3d<float>& N);

	float getAngleAccelerationZ(float x1, float x2, float x3, const Math::Vector3d<float>& I, const Math::Vector3d<float>& N);
};
	}
}

#endif