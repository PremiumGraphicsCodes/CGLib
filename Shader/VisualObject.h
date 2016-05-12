#ifndef __CRYSTAL_SHADER_VISUAL_OBJECT_H__
#define __CRYSTAL_SHADER_VISUAL_OBJECT_H__

#include "../Polygon/PolygonObject.h"
#include "../Polygon/ParticleObject.h"

#include "../Graphics/PointBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/TriangleBuffer.h"

#include "../Graphics/Light.h"

#include "../Graphics/ICamera.h"

#include "LegacyRenderer.h"

namespace Crystal {
	namespace Physics {
		class PhysicsObject;
	}
	namespace Shader {

class VisualObject
{
public:

	VisualObject(const Polygon::ParticleObject& particle);

	VisualObject(const Polygon::ActorObject& actor);

	VisualObject(const Polygon::PolygonMesh& polygon);

	VisualObject(const Physics::PhysicsObject& physics);

	VisualObject(const Polygon::VolumeObject& volume);

	void renderPoints(const Graphics::ICamera<float>& camera)
	{
		renderer.render(camera, pointBuffer);
	}

	void renderPointIds(const Graphics::ICamera<float>& camera)
	{
		renderer.renderId(camera, pointBuffer);
	}

	void renderLines(const Graphics::ICamera<float>& camera)
	{
		renderer.render(camera, lineBuffer);
	}

	void renderLineIds(const Graphics::ICamera<float>& camera)
	{
		renderer.renderId(camera, lineBuffer);
	}

	void renderTriangles(const Graphics::ICamera<float>& camera);


private:
	LegacyRenderer renderer;


	Graphics::PointBuffer pointBuffer;
	Graphics::LineBuffer lineBuffer;
	Graphics::TriangleBuffer triangleBuffer;



};


	}
}

#endif