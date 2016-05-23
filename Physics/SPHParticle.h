#ifndef __CRYSTAL_PHYSICS_SPH_PARTICLE_H__
#define __CRYSTAL_PHYSICS_SPH_PARTICLE_H__

#include <list>
#include <vector>
#include <memory>

#include "../Math/Vector3d.h"
#include "../Polygon/Particle.h"

#include "../Util/UnCopyable.h"
#include "SPHConstant.h"

namespace Crystal{
	namespace Physics{
		class Coordinator;


class SPHParticle: public Polygon::Particle, private UnCopyable
{
public:
	SPHParticle(const int id = -1);

	SPHParticle(const Particle& particle, SPHConstant* constant);

	SPHParticle(const Math::Vector3d<float>& center, float radius, SPHConstant* constant, const int id = -1);

	virtual ~SPHParticle() {};

	float getDensityRatio() const;

	float getPressure() const;

	float getMass() const;

	float getVolume() const;

	float getRestVolume() const;

	void addForce(const Math::Vector3d<float>& force) { this->force += force; }

	void setForce( const Math::Vector3d<float>& force ) { this->force = force; }

	Math::Vector3d<float> getForce() const { return force; }

	void setDefaultDensity() { this->density = constant->getDensity(); }

	float getDensity() const { return density; }

	void addDensity(const float density) { this->density += density; }

	void init();

	Math::Vector3d<float> getAccelaration() { return force / density; }

	Math::Vector3d<float> getVelocity() const { return velocity; }

	void setVelocity( const Math::Vector3d<float>& velocity ) { this->velocity = velocity; }

	void addVelocity(const Math::Vector3d<float>& velocity) { this->velocity += velocity; }

	void forwardTime(const float timeStep);

	void addExternalForce(const Math::Vector3d<float>& force);

	void solveNormal(const SPHParticle& rhs);

	void solveSurfaceTension(const SPHParticle& rhs);

	void solvePressureForce(const SPHParticle& rhs);

	void solveViscosityForce(const SPHParticle& rhs);

	void addSelfDensity();

	void addDensity(const SPHParticle& rhs);

	Math::Vector3d<float> getNormal() const { return normal; }

	bool isBoundary() const { return constant->isBoundary; }

private:
	Math::Vector3d<float> force;
	Math::Vector3d<float> velocity;
	Math::Vector3d<float> normal;
	SPHConstant* constant;
};

	}
}

#endif