#include "BulletBoundary.h"
#include "ParticlePair.h"
#include "PhysicsObject.h"

using namespace Crystal::Physics;

std::vector<ParticlePair> BulletBoundary::createPairs()
{
	BulletRigid rigid(bulletRigid);
	const auto& particles1 = rigid.toSurfaceParticles();
	const auto& particles2 = physicsObject->getParticles();

	return std::vector< ParticlePair >();
}

BulletBoundary::BulletBoundary(PhysicsObject* physicsObject, btRigidBody* bulletRigid) :
	physicsObject(physicsObject),
	bulletRigid(bulletRigid)
{
}
