#ifndef __CRYSTAL_PHYSICS_BULLET_INTERACTION_H__
#define __CRYSTAL_PHYSICS_BULLET_INTERACTION_H__

#include <map>

namespace Crystal {
	namespace Physics {

class PhysicsObject;
class btRigidBody;

class ParticleBulletMap
{
public:
	void clear() {
		particleRigidMap.clear();
		rigidParticleMap.clear();
	}

	void add(PhysicsObject* particle, btRigidBody* rigid) {
		particleRigidMap[particle] = rigid;
		rigidParticleMap[rigid] = particle;
	}

	btRigidBody* find(PhysicsObject* object) {
		return nullptr;
	}

	PhysicsObject* find(btRigidBody* body) {
		return nullptr;
	}
private:
	std::map< PhysicsObject*, btRigidBody* > particleRigidMap;
	std::map< btRigidBody*, PhysicsObject* > rigidParticleMap;
};

class BulletInteraction
{
public:
private:
	ParticleBulletMap map;
};
	}
}

#endif
