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
	namespace Shader {

		enum class RenderingMode {
			Surface,
			Wireframe,
			Point,
			ID,
			Volume,
		};


class IVisualObject
{
public:
	IVisualObject(const Polygon::ParticleObject& particle)
	{
		pointBuffer.add(particle);
	}

	IVisualObject(const Polygon::ActorObject& actor)
	{
		lineBuffer.add(actor);
	}



	IVisualObject(const Polygon::PolygonObject& polygon)
	{
		pointBuffer.add(polygon);
		lineBuffer.add(polygon);
		triangleBuffer.add(polygon);
	}

	void renderPoints(const Graphics::ICamera<float>& camera)
	{
		renderer.render(camera, pointBuffer);
	}

	void renderLines(const Graphics::ICamera<float>& camera)
	{
		renderer.render(camera, lineBuffer);
	}

	void renderTriangles(const Graphics::ICamera<float>& camera){
		Graphics::PointLight<float> light;
		light.setPos(Math::Vector3d<float>(-10.0, 10.0, 10.0));
		light.setDiffuse(Graphics::ColorRGBA<float>(1.0, 1.0, 1.0, 1.0));

		renderer.render(camera, light, triangleBuffer);
	}

private:
	LegacyRenderer renderer;

	Graphics::PointBuffer pointBuffer;
	Graphics::LineBuffer lineBuffer;
	Graphics::TriangleBuffer triangleBuffer;

};


class VisualObject
{
public:

	~VisualObject() {
		clear();
	}

	void add(IVisualObject* object) {
		objects.push_back(object);
	}

	void clear() {
		for (auto o : objects) {
			delete o;
		}
		objects.clear();
	}

	void render(const Graphics::ICamera<float>& camera, RenderingMode mode);

private:

	Shader::LegacyRenderer renderer;
	std::list<IVisualObject*> objects;
	//VisualPoint point;
	//VisualLine line;
	//VisualTriangle triangle;

};

	}
}

#endif