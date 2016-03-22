#include "BulletInteraction.h"

//#include "../ThirdParty/bullet/src/btBulletCollisionCommon.h"
#include "../ThirdParty/bullet/src/btBulletDynamicsCommon.h"
#include "PhysicsWorld.h"
#include "BulletRigid.h"

//using namespace Crystal::Math;
using namespace Crystal::Physics;

BulletInteraction::BulletInteraction(ParticleWorld* particleWorld, BulletWorld* bulletWorld) :
	particleWorld( particleWorld ),
	bulletWorld( bulletWorld )
{
}

void BulletInteraction::add(BulletRigid* bulletRigid)
{
	const auto& rigids = bulletWorld->getRigids();
	for (auto& r : rigids) {
		const auto& ps = r->getSurfaceParticles();
		particleWorld->add(ps);
	}
}

void BulletInteraction::simulate(const float timeStep)
{
	const auto& rigids = bulletWorld->getRigids();
	for (auto& r : rigids) {
		r->transform();
	}

	particleWorld->simulate(1.25f, timeStep*10);
	bulletWorld->simulate(timeStep);
}
