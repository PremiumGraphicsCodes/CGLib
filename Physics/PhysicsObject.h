#ifndef __CRYSTAL_PHYSICS_PHYSICS_OBJECT_H__
#define __CRYSTAL_PHYSICS_PHYSICS_OBJECT_H__

#include <vector>

namespace Crystal {
	namespace Physics {
		class Particle;

class PhysicsObject {
public:
	PhysicsObject() {};

	PhysicsObject(const std::vector<Particle*>& particles);

	virtual ~PhysicsObject();

	virtual void coordinate() {};

	std::vector<Particle*> getParticles() const { return particles; }

	float getMass() const;

	float getRestVolume() const;

	void clear() {
		particles.clear();
	}


private:
	std::vector<Particle*> particles;
};


	}
}

#endif