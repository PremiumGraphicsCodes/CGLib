#ifndef __CRYSTAL_SAMPLE_BULLET_RIGID_SAMPLE_H__
#define __CRYSTAL_SAMPLE_BULLET_RIGID_SAMPLE_H__

#include "glfw.h"
#include "../Physics/Bullet.h"
#include "../Physics/BulletWorld.h"

#include "../Physics/Fluid.h"
#include "../Physics/PhysicsWorld.h"
#include "../Physics/BulletRigid.h"
#include "../Polygon/PolygonObject.h"
#include "ISample.h"
#include <memory>
#include <map>

class RigidSample : public ISample
{
public:
	RigidSample() {}

	void setup();

	void demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera) override;

	void onMiddleButtonDown(const float x, const float y) override;

private:

	void cleanup() {};

	std::unique_ptr< Crystal::Physics::BulletRigid > rigid1;
	std::unique_ptr< Crystal::Physics::BulletRigid > rigid2;
	std::unique_ptr< Crystal::Physics::BulletRigid > rigid3;
	Crystal::Polygon::PolygonObject shape1;
	Crystal::Polygon::PolygonObject shape2;
	Crystal::Polygon::PolygonObject shape3;

	std::map< Crystal::Physics::BulletRigid*, Crystal::Polygon::PolygonObject* > rigidPolygonMap;

	std::unique_ptr< Crystal::Physics::BulletRigid > ground;
	Crystal::Physics::BulletWorld world;
	Crystal::Physics::SPHConstant constant;

};

#endif