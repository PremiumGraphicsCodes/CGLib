#ifndef __CRYSTAL_PHYSICS_BULLET_MAP_H__
#define __CRYSTAL_PHYSICS_BULLET_MAP_H__

#include <map>

class btRigidBody;

namespace Crystal {
	namespace Physics {

class PhysicsObject;

class BulletMap
{
public:
	void clear();

	void set(PhysicsObject* particle, btRigidBody* rigid) {
		particleRigidMap[particle] = rigid;
		rigidParticleMap[rigid] = particle;
	}

	btRigidBody* find(PhysicsObject* object);

	PhysicsObject* find(btRigidBody* body);

private:
	std::map< PhysicsObject*, btRigidBody* > particleRigidMap;
	std::map< btRigidBody*, PhysicsObject* > rigidParticleMap;
};

	}
}

#endif