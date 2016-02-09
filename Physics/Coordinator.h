#ifndef __CRYSTAL_PHYSICS_COORDINATOR_H__
#define __CRYSTAL_PHYSICS_COORDINATOR_H__

#include <vector>

#include "Particle.h"

#include "../Math/Vector3d.h"

#include "../Util/UnCopyable.h"

#include <memory>

namespace Crystal{
	namespace Physics{

class Coordinator : private UnCopyable
{
public:
	Coordinator()
	{};

	virtual ~Coordinator(){}

	virtual void coordinate( const std::vector<Particle*>& particles ) = 0;
};

using CoordinatorSPtr = std::shared_ptr < Coordinator > ;
using CoordinatorSPtrVector = std::vector<CoordinatorSPtr>;

class EulerIntegrator final : public Coordinator
{
public:
	EulerIntegrator(const float timeStep) :
		timeStep( timeStep )
	{
	}
	
	virtual void coordinate(const std::vector<Particle*>& particles) override {
		for (const auto& particle : particles) {
			const auto& accelaration = particle->getAccelaration();//particle->variable.force / particle->variable.density;
			particle->addVelocity(accelaration * timeStep);
			particle->addCenter(particle->getVelocity() * timeStep);
		}
	}

	float getTimeStep() const { return timeStep; }

private:
	const float timeStep;
};


class ExternalForceCoordinator final : public Coordinator
{
public:
	ExternalForceCoordinator(const Math::Vector3d<float>& force, const float timeStep) :
		force( force ),
		timeStep( timeStep )
	{}

	virtual void coordinate(const std::vector<Particle*>& particles) override {
		for (const auto& particle : particles) {
			particle->addForce(force * particle->getDensity());
		}
	}

	Math::Vector3d<float> getForce() const { return force; }

	void addForce( const Math::Vector3d<float>& force ) { this->force += force; }

	float getTimeStep() const { return timeStep; }

private:
	Math::Vector3d<float> force;
	const float timeStep;
};

	}
}

#endif