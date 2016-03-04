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

	float getAngleAccelerationX(float x1, float x2, float x3, const Math::Vector3d<float>& I, const Math::Vector3d<float>& N)
	{
		return (N.getX() + (I.getY() - I.getZ()) * x2 * x3) / I.getX() - 10.0f * x1;
	}

	float getAngleAccelerationY(float x1, float x2, float x3, const Math::Vector3d<float>& I, const Math::Vector3d<float>& N)
	{
		return (N.getY() + (I.getZ() - I.getX()) * x3 * x1) / I.getY() - 10.0f * x2;
	}

	float getAngleAccelerationZ(float x1, float x2, float x3, const Math::Vector3d<float>& I, const Math::Vector3d<float>& N)
	{
		return (N.getZ() + (I.getX() - I.getY()) * x1 * x2) / I.getZ() - 10.0f * x3;
	}
};
	}
}

#endif