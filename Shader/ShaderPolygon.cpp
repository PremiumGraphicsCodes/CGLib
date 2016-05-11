#include "ShaderPolygon.h"
#include "../Polygon/PolygonObject.h"
#include "../Graphics/Light.h"
#include "../Graphics/Material.h"
#include <algorithm>

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

ShaderPolygon::ShaderPolygon(const VisualPolygon& vp)
{
	renderer.build();
	renderer.findLocation();

	triangleBuffer.add(*vp.getPolygon());
	this->materialMaps = vp.getMaterialMaps();
}


void ShaderPolygon::setup(const VisualPolygon& vp)
{
	renderer.build();
	renderer.findLocation();

	triangleBuffer.add(*vp.getPolygon());
	this->materialMaps = vp.getMaterialMaps();
	/*
	for (auto m : this->materialMaps) {
		const auto& ambient = m.getMaterial().getTextures().getAmbient();
		if (ambient.hasFileName()) {
			ambientTexture.create( ambient.toImagef(), 0 );
		}
		const auto& diffuse = m.getMaterial().getTextures().getDiffuse();
		if (diffuse.hasFileName()) {
			diffuseTexture.create(diffuse.toImagef(), 1);
		}
	}
	*/
}

void ShaderPolygon::draw(const ICamera<float>& camera, const PointLight<float>& light)
{
	renderer.render(camera, triangleBuffer, light, materialMaps);
}