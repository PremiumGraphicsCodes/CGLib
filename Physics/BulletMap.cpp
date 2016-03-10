#include "BulletMap.h"

using namespace Crystal::Physics;

void BulletMap::clear()
{
	particleRigidMap.clear();
	rigidParticleMap.clear();
}

btRigidBody* BulletMap::find(PhysicsObject* object)
{
	return nullptr;
}

PhysicsObject* BulletMap::find(btRigidBody* body)
{
	return nullptr;
}
