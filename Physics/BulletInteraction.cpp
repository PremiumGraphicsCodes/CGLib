#include "BulletInteraction.h"

//#include "../ThirdParty/bullet/src/btBulletCollisionCommon.h"
#include "../ThirdParty/bullet/src/btBulletDynamicsCommon.h"
#include "PhysicsWorld.h"
#include "BulletRigid.h"

using namespace Crystal::Math;
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
		particleWorld->add(r);
		r->transform();
	}
}

void BulletInteraction::setExternalForce(const Vector3d<float>& f)
{
	particleWorld->setExternalForce(f);
	bulletWorld->setExternalForce(f);
}


void BulletInteraction::simulate(const float timeStep)
{
	const auto& rigids = bulletWorld->getRigids();
	for (auto& r : rigids) {
		r->transform();
	}

	//for (int i = 0; i < 10; ++i) {
	particleWorld->simulate(1.25f, timeStep);// / 10.0f);
	//}
	for (auto& r : rigids) {
		r->solveBoundary();
	}

	bulletWorld->simulate(timeStep);

}

void BulletInteraction::setBoundary(const Box<float>& box)
{
	particleWorld->setBoundary(box);
	bulletWorld->setBoundary(box);
}
