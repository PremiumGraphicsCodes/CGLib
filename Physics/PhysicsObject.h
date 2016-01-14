#ifndef __CRYSTAL_PHYSICS_PHYSICS_OBJECT_H__
#define __CRYSTAL_PHYSICS_PHYSICS_OBJECT_H__

#include "Coordinator.h"

namespace Crystal {
	namespace Physics {

template<typename GeomType>
class PhysicsObject {
public:
	PhysicsObject() {};

	PhysicsObject(const ParticleSPtrVector<GeomType>& particles ) :
		particles(particles)
	{}


	PhysicsObject( const ParticleSPtrVector<GeomType>& particles, const CoordinatorSPtrVector& coordinators ) :
		particles( particles ),
		coordinators( coordinators )
	{}

	virtual ~PhysicsObject() {
		clear();
	}

	void coordinate() const {
		for (const auto& coordinator : coordinators) {
			coordinator->coordinate(particles);
		}
	}

	ParticleSPtrVector<GeomType> getParticles() const { return particles; }

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
	ParticleSPtrVector<GeomType> particles;
	CoordinatorSPtrVector coordinators;
};


	}
}

#endif