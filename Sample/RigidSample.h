#ifndef __CRYSTAL_SAMPLE_BULLET_RIGID_SAMPLE_H__
#define __CRYSTAL_SAMPLE_BULLET_RIGID_SAMPLE_H__

#include "glfw.h"
#include "../Physics/Bullet.h"
#include "../Physics/BulletWorld.h"

#include "../Physics/Fluid.h"
#include "../Physics/PhysicsWorld.h"
#include "../Physics/BulletRigid.h"
#include "../Polygon/PolygonMesh.h"
#include "../Shader/SmoothRenderer.h"
#include "ISample.h"
#include <memory>
#include <map>

class RigidSample : public ISample
{
public:
	RigidSample() {}

	void setup() override;

	void cleanup() override;

	void demonstrate(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera) override;

	void onMiddleButtonDown(const float x, const float y) override;

private:

	std::vector< Crystal::Physics::BulletRigid* > rigids;
	std::vector<  Crystal::Core::PolygonMesh*> shapes;

	std::unique_ptr< Crystal::Physics::BulletRigid > ground;
	Crystal::Physics::BulletWorld world;
	Crystal::Physics::SPHConstant constant;
	Crystal::Shader::SmoothRenderer smoothRenderer;

};

#endif