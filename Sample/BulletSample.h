#ifndef __CRYSTAL_SAMPLE_BULLET_SAMPLE_H__
#define __CRYSTAL_SAMPLE_BULLET_SAMPLE_H__

#include "glfw.h"
#include "../../bullet/src/btBulletDynamicsCommon.h"


class BulletSample
{
public:
	BulletSample();

	~BulletSample();

	void setup();

	void demonstrate();

	void cleanup();
private:
	GLFWwindow* window;
	btDefaultCollisionConfiguration collisionConfig;
	btCollisionDispatcher dispatcher;
	btDbvtBroadphase overlappingPairCache;
	btSequentialImpulseConstraintSolver solver;
	btDiscreteDynamicsWorld world;
	btRigidBody* rigid;
};

#endif
