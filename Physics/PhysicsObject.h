#ifndef __CRYSTAL_PHYSICS_PHYSICS_OBJECT_H__
#define __CRYSTAL_PHYSICS_PHYSICS_OBJECT_H__

#include <vector>

#include "../Math/Vector3d.h"
#include "../Math/Box3d.h"
#include "../Math/Sphere.h"
#include "../Math/Index3d.h"
#include "SPHConstant.h"

namespace Crystal {
	namespace Core {
		class ParticleObject;
		class PolygonMesh;
	}
	namespace Physics {
		class SPHParticle;

class PhysicsObject
{
public:
	PhysicsObject() {};

	PhysicsObject(const Math::Box3d<float>& box, const float divideLength, const SPHConstant& constant);

	PhysicsObject(const Math::Sphere<float>& sphere, const float divideLength, const SPHConstant& constant);

	PhysicsObject(const std::vector<SPHParticle*>& particles);

	SPHParticle* createParticle(const Math::Vector3d<float>& position, const Math::Vector3d<float>& velocity);

	std::vector<SPHParticle*> createParticles(const Math::Box3d<float>& box, const float divideLength);

	std::vector<SPHParticle*> createParticles(const Math::Sphere<float>& sphere, const float divideLength);

	virtual ~PhysicsObject();

	virtual void coordinate(const float timeStep) {};

	std::vector<SPHParticle*> getParticles() const { return particles; }

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

	Core::ParticleObject* toParticleObject() const;

	Core::ParticleObject* toSurfaceParticleObject() const;

	Core::PolygonMesh* toPolygonObject(const float isolevel,const float effectLength, const Math::Space3d<float>& space) const;


private:
	int nextId;
	std::vector<SPHParticle*> particles;
	SPHConstant constant;
};


	}
}

#endif