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
#include "../Shader/ShaderObject.h"
#include "../Shader/PointRenderer.h"
#include "../Graphics/ColorMap.h"
#include "ISample.h"
#include <memory>
#include <map>

class BulletInteractionSample : public ISample
{
public:
	BulletInteractionSample() {}

	void setup();

	virtual void onMouseMove(const float x, const float y) override;

	void demonstrate(const Crystal::Graphics::ICamera<float>& camera);

	void onKeyDown(const unsigned char c);


private:

	void cleanup() override;

	std::vector< Crystal::Physics::BulletRigid* > rigids;
	std::vector< Crystal::Polygon::PolygonObject* > shapes;

	Crystal::Physics::BulletRigid* selected;

	std::map< Crystal::Physics::BulletRigid*, Crystal::Polygon::PolygonObject* > rigidPolygonMap;

	std::unique_ptr< Crystal::Physics::BulletRigid > ground;
	std::unique_ptr< Crystal::Physics::Fluid > fluid;
	Crystal::Physics::ParticleWorld particleWorld;
	Crystal::Physics::BulletWorld bulletWorld;
	Crystal::Physics::BulletInteraction interaction;
	Crystal::Physics::SPHConstant constant;
	Crystal::Physics::SPHConstant rigidConstant;
	Crystal::Graphics::ColorMap colorMap;

	Crystal::Shader::ShaderObject shader;
	std::unique_ptr< Crystal::Shader::PointRenderer<float> > pointRenderer;


};

#endif