#ifndef __CRYSTAL_PHYSICS_PHYSICS_OBJECT_H__
#define __CRYSTAL_PHYSICS_PHYSICS_OBJECT_H__

#include <vector>

#include "../Math/Vector3d.h"

namespace Crystal {
	namespace Physics {
		class Particle;

class PhysicsObject {
public:
	PhysicsObject() {};

	PhysicsObject(const std::vector<Particle*>& particles);

	virtual ~PhysicsObject();

	virtual void coordinate(const float timeStep) {};

	std::vector<Particle*> getParticles() const { return particles; }

	float getMass() const;

	float getRestVolume() const;

	void clear() {
		particles.clear();
	}

	void forwardTime(const float timeStep);

	void addExternalForce(const Math::Vector3d<float>& force);

	Math::Vector3d<float> getCenter() const;

	Math::Vector3d<float> getAverageVelosity() const;

	float getWeight() const;

	void convertToFluidForce();

	void move(const Math::Vector3d<float>& v);

	void setVelocity(const Math::Vector3d<float>& velocity);

private:
	std::vector<Particle*> particles;
};


	}
}

#endif