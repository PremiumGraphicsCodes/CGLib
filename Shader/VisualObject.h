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
	virtual void add(const Polygon::ParticleObject& point) = 0;
	virtual void add(const Polygon::ActorObject& actor) = 0;
	virtual void add(const Polygon::PolygonObject& polygon) = 0;

	virtual void clear() = 0;

	virtual void render(const Graphics::ICamera<float>& camera) = 0;
};

class VisualPoint : public IVisualObject
{
public:
	virtual void add(const Polygon::ParticleObject& particle) override {
		buffer.add(particle);
	}

	virtual void add(const Polygon::PolygonObject& polygon) override {
		buffer.add(polygon);
	}

	virtual void add(const Polygon::ActorObject& actor) override {
		buffer.add(actor);
	}

	virtual void clear() override{
		buffer.clear();
	}

	virtual void render(const Graphics::ICamera<float>& camera) override {
		LegacyRenderer renderer;
		renderer.render(camera, buffer);
	}


private:
	Graphics::PointBuffer buffer;

};

class VisualLine : public IVisualObject
{
public:
	virtual void add(const Polygon::ParticleObject& particle) override {
		;
	}

	virtual void add(const Polygon::PolygonObject& polygon) override {
		buffer.add(polygon);
	}

	virtual void add(const Polygon::ActorObject& actor) override {
		buffer.add(actor);
	}

	virtual void clear() override {
		buffer.clear();
	}

	virtual void render(const Graphics::ICamera<float>& camera) override {
		LegacyRenderer renderer;
		renderer.render(camera, buffer);
	}



private:
	Graphics::LineBuffer buffer;

};

class VisualTriangle : public IVisualObject
{
public:
	VisualTriangle(const Polygon::PolygonObject& polygon) {
		buffer.add(polygon);
	}

	virtual void add(const Polygon::ParticleObject& particle) override {
		;
	}


	virtual void add(const Polygon::PolygonObject& polygon) override {
		buffer.add(polygon);
	}


	void add(const Polygon::ActorObject& actor) override
	{
		;//buffer.add(actor);
		//triangleBuffer.add(actor);
	}

	virtual void clear() override {
		buffer.clear();
	}

	virtual void render(const Graphics::ICamera<float>& camera) override {
		LegacyRenderer renderer;
		Graphics::PointLight<float> light;
		light.setPos(Math::Vector3d<float>(-10.0, 10.0, 10.0));
		light.setDiffuse(Graphics::ColorRGBA<float>(1.0, 1.0, 1.0, 1.0));

		renderer.render(camera, light, buffer);
	}

private:
	Graphics::TriangleBuffer buffer;
	//Graphics::PointLight<float> light;

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

	void add(const Polygon::ParticleObject& particle) {
		for (auto o : objects) {
			o->add(particle);
		}
	}


	void add(const Polygon::PolygonObject& polygon) {
		for (auto o : objects) {
			o->add(polygon);
		}
	}


	void add(const Polygon::ActorObject& actor) {
		for (auto o : objects) {
			o->add(actor);
		}
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