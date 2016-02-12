#include "GLee.h"
#include "VisualObject.h"

#include "../Graphics/Light.h"

using namespace Crystal::Math;
using namespace Crystal::Graphics;
using namespace Crystal::Shader;
using namespace Crystal::Polygon;

VisualObject::VisualObject(const ParticleObject& particle)
{
	pointBuffer.add(particle);
}

VisualObject::VisualObject(const ActorObject& actor)
{
	lineBuffer.add(actor);
}

VisualObject::VisualObject(const PolygonObject& polygon)
{
	pointBuffer.add(polygon);
	lineBuffer.add(polygon);
	triangleBuffer.add(polygon);
}

void VisualObject::renderTriangles(const ICamera<float>& camera)
{
	Graphics::PointLight<float> light;
	light.setPos(Math::Vector3d<float>(-10.0, 10.0, 10.0));
	light.setDiffuse(Graphics::ColorRGBA<float>(1.0, 1.0, 1.0, 1.0));

	renderer.render(camera, light, triangleBuffer);
}
