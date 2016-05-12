#include "VisualMaterial.h"

#include "../Graphics/MaterialMap.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

VisualMaterial::VisualMaterial(const MaterialMap& material)
{
	load(material);
}

bool VisualMaterial::load(const MaterialMap& mm)
{
	this->startFaceIndex = mm.getStartFaceIndex();
	this->endFaceIndex = mm.getEndFaceIndex();

	const auto& material = mm.getMaterial();

	ambientColor = material.getAmbient().toArray3();
	diffuseColor = material.getDiffuse().toArray3();
	specularColor = material.getSpecular().toArray3();
	shininess = material.getShininess();

	const auto& texture = material.getTexture();
	this->diffuseTex.create(texture.toImagef(), 0);
	return true;
}
