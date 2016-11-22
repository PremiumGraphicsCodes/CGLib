#ifndef __CRYSTAL_PHYSICS_PBSPH_OBJECT_H__
#define __CRYSTAL_PHYSICS_PBSPH_OBJECT_H__

#include <vector>

#include "../Math/Vector3d.h"
#include "../Math/Box3d.h"
#include "../Math/Sphere.h"
#include "../Math/Index3d.h"
#include "PBSPHConstant.h"

namespace Crystal {
	namespace Core {
		class ParticleObject;
		class PolygonMesh;
	}
	namespace Physics {
		class PBSPHParticle;

class PBSPHObject
{
public:
	PBSPHObject() {};

	PBSPHObject(const Math::Box3d<float>& box, const float divideLength, const PBSPHConstant& constant);

	PBSPHObject(const Math::Sphere<float>& sphere, const float divideLength, const PBSPHConstant& constant);

	PBSPHObject(const std::vector<PBSPHParticle*>& particles);

	PBSPHParticle* createParticle(const Math::Vector3d<float>& position, const Math::Vector3d<float>& velocity);

	std::vector<PBSPHParticle*> createParticles(const Math::Box3d<float>& box, const float divideLength);

	std::vector<PBSPHParticle*> createParticles(const Math::Sphere<float>& sphere, const float divideLength);

	virtual ~PBSPHObject();

	virtual void coordinate(const float timeStep) {};

	std::vector<PBSPHParticle*> getParticles() const { return particles; }

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

	Core::PolygonMesh* toPolygonObject(const float isolevel, const int levelOfDetail, const Math::Space3d<float>& space) const;


private:
	int nextId;
	std::vector<PBSPHParticle*> particles;
	PBSPHConstant constant;
};

	}
}

#endif