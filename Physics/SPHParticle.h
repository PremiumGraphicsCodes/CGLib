#ifndef __CRYSTAL_PHYSICS_SPH_PARTICLE_H__
#define __CRYSTAL_PHYSICS_SPH_PARTICLE_H__

#include <list>
#include <vector>
#include <memory>

#include "../Math/Vector3d.h"
#include "../Polygon/Particle.h"

#include "../Util/UnCopyable.h"

namespace Crystal{
	namespace Physics{
		class Coordinator;

class SPHParticle final : public Polygon::Particle, private UnCopyable
{
public:
	SPHParticle();

	SPHParticle(const Particle& particle, float pressureCoe = 1.0f, float viscosityCoe = 0.0f);

	SPHParticle(const Math::Vector3d<float>& center, float radius, float density, float pressureCoe = 1.0f, float viscosityCoe = 0.0f);

	float getDensityRatio() const;

	float getPressure() const;

	float getMass() const;

	float getVolume() const;

	float getRestVolume() const;

	void addForce(const Math::Vector3d<float>& force) { this->force += force; }

	void setForce( const Math::Vector3d<float>& force ) { this->force = force; }

	Math::Vector3d<float> getForce() const { return force; }

	float getDensity() const { return density; }

	void addDensity(const float density) { this->density += density; }

	float getRestDensity() const { return restDensity; }

	void init() {
		density = 0.0;
		force = Math::Vector3d<float>( 0.0f, 0.0f, 0.0f);
	}


	Math::Vector3d<float> getAccelaration() { return force / density; }

	Math::Vector3d<float> getVelocity() const { return velocity; }

	void setVelocity( const Math::Vector3d<float>& velocity ) { this->velocity = velocity; }

	void addVelocity(const Math::Vector3d<float>& velocity) { this->velocity += velocity; }

	float getViscosityCoe() const { return viscosityCoe; }

	void forwardTime(const float timeStep);

	void addExternalForce(const Math::Vector3d<float>& force);

public:
	void setGridID( const float effectLength ) {
		const Math::Vector3d<float>& point = getPosition();
		int gridX = static_cast<int>( point.getX() / effectLength );
		int gridY = static_cast<int>( point.getY() / effectLength );
		int gridZ = static_cast<int>( point.getZ() / effectLength );
		gridID = getID( gridX, gridY, gridZ );
	}

	int getGridID() const { return gridID; }

	static bool compare(const SPHParticle* lhs, const SPHParticle* rhs){
		return lhs->getGridID() < rhs->getGridID();
	}


private:
	int getID( int idX, int idY, int idZ ) const {
		return (idZ << 20) + (idY << 10) + idX;
	}

	float restDensity;
	float density;
	Math::Vector3d<float> force;
	Math::Vector3d<float> velocity;
	float pressureCoe;
	float viscosityCoe;

	int gridID;
};

	}
}

#endif