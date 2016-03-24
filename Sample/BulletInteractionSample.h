#ifndef __CRYSTAL_SAMPLE_BULLET_INTERACTION_SAMPLE_H__
#define __CRYSTAL_SAMPLE_BULLET_INTERACTION_SAMPLE_H__

#include "glfw.h"
#include "../Physics/Bullet.h"
#include "../Physics/BulletWorld.h"
#include "../Physics/BulletInteraction.h"

#include "../Physics/Fluid.h"
#include "../Physics/PhysicsWorld.h"
#include "../Physics/BulletRigid.h"
#include "../Polygon/PolygonObject.h"
#include "ISample.h"
#include <memory>
#include <map>

class BulletInteractionSample : public ISample
{
public:
	BulletInteractionSample() {}

	void setup();

	void demonstrate();

private:

	void cleanup() {};

	std::vector< Crystal::Physics::BulletRigid* > rigids;
	std::vector< Crystal::Polygon::PolygonObject* > shapes;


	std::map< Crystal::Physics::BulletRigid*, Crystal::Polygon::PolygonObject* > rigidPolygonMap;

	std::unique_ptr< Crystal::Physics::BulletRigid > ground;
	std::unique_ptr< Crystal::Physics::Fluid > fluid;
	Crystal::Physics::ParticleWorld particleWorld;
	Crystal::Physics::BulletWorld bulletWorld;
	Crystal::Physics::BulletInteraction interaction;
	Crystal::Physics::SPHConstant constant;

};

#endif