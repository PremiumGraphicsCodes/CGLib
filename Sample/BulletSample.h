#ifndef __CRYSTAL_SAMPLE_BULLET_SAMPLE_H__
#define __CRYSTAL_SAMPLE_BULLET_SAMPLE_H__

#include "glfw.h"
#include "../ThirdParty/bullet/src/btBulletDynamicsCommon.h"
#include "ISample.h"

class BulletSample : public ISample
{
public:
	BulletSample();

	void setup() override;

	void demonstrate(const Crystal::Graphics::ICamera<float>& camera) override;

private:
	btDefaultCollisionConfiguration collisionConfig;
	btCollisionDispatcher dispatcher;
	btDbvtBroadphase overlappingPairCache;
	btSequentialImpulseConstraintSolver solver;
	btDiscreteDynamicsWorld world;
	btRigidBody* rigid;
	btRigidBody* rigid2;
};

#endif
