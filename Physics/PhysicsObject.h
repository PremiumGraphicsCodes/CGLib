#ifndef __CRYSTAL_PHYSICS_PHYSICS_OBJECT_H__
#define __CRYSTAL_PHYSICS_PHYSICS_OBJECT_H__

#include "Coordinator.h"

namespace Crystal {
	namespace Physics {

class PhysicsObject {
public:
	PhysicsObject() {};

	PhysicsObject(const std::vector<Particle*>& particles);

	PhysicsObject(const std::vector<Particle*>& particles, const CoordinatorSPtrVector& coordinators);

	virtual ~PhysicsObject();

	void coordinate() const;

	std::vector<Particle*> getParticles() const { return particles; }

	float getMass() const {
		auto weight = 0.0f;
		for (const auto& particle : particles) {
			weight += particle->getMass();
		}
		return weight;
	}

	float getRestVolume() const {
		auto volume = 0.0f;
		for (const auto& particle : particles) {
			volume += particle->getRestVolume();
		}
		return volume;
	}

	void clear() {
		particles.clear();
		coordinators.clear();
	}


private:
	std::vector<Particle*> particles;
	CoordinatorSPtrVector coordinators;
};


	}
}

#endif