#ifndef __CRYSTAL_PHYSICS_IISPH_PARTICLE_H__
#define __CRYSTAL_PHYSICS_IISPH_PARTICLE_H__

#include <list>

#include "../Math/Vector3d.h"
#include "../Core/Particle.h"
#include "../Util/UnCopyable.h"
#include "SPHConstant.h"

namespace Crystal {
	namespace Physics {

class IISPHParticle : public Core::Particle, private UnCopyable
{
public:
	IISPHParticle(const int id = -1);

	IISPHParticle(const Particle& particle, SPHConstant* constant);

	IISPHParticle(const Math::Vector3d<float>& center, float radius, SPHConstant* constant, const int id = -1);

	virtual ~IISPHParticle() {};

	void setNeighbors(const std::list<IISPHParticle*>& neighbors);

	std::list<IISPHParticle*> getNeighbors() const { return neighbors; }

	float getDensityRatio() const;

	float getPressure() const;

	float getMass() const;

	float getVolume() const;

	float getRestVolume() const;

	void addForce(const Math::Vector3d<float>& force) { this->force += force; }

	void setForce(const Math::Vector3d<float>& force) { this->force = force; }

	Math::Vector3d<float> getForce() const { return force; }

	void setDefaultDensity() { this->density = constant->getDensity(); }

	float getDensity() const { return density; }

	void addDensity(const float density) { this->density += density; }

	void init();

	Math::Vector3d<float> getAccelaration() { return force / density; }

	Math::Vector3d<float> getVelocity() const { return velocity; }

	void setVelocity(const Math::Vector3d<float>& velocity) { this->velocity = velocity; }

	void addVelocity(const Math::Vector3d<float>& velocity) { this->velocity += velocity; }

	void forwardTime(const float timeStep);

	void addExternalForce(const Math::Vector3d<float>& force);

	void solvePressureForce(const IISPHParticle& rhs);

	void solveViscosityForce(const IISPHParticle& rhs);

	void addSelfDensity();

	void addDensity(const IISPHParticle& rhs);

	Math::Vector3d<float> getNormal() const { return normal; }

	bool isBoundary() const { return constant->isBoundary; }

	void predictAdvection1(const Math::Vector3d<float>& externalForce, const float dt);

	void predictAdvection2(const float dt);

	void solveDijPj(const float dt);

	void solvePressure(const float dt);

	void integrate(const float dt);

	void solveDensity();

public:
	Math::Vector3d<float> getDii(IISPHParticle* rhs, const float dt) const;

	Math::Vector3d<float> getDij(IISPHParticle* rhs, const float dt) const;


	Math::Vector3d<float> force;
	Math::Vector3d<float> velocity;
	Math::Vector3d<float> normal;
	SPHConstant* constant;
	std::list<IISPHParticle*> neighbors;
	Math::Vector3d<float> advVelocity;
	Math::Vector3d<float> dii;
	float advDensity;
	float coe;
	float aii;
	Math::Vector3d<float> dijp;
	float pressure;
};

	}
}

#endif