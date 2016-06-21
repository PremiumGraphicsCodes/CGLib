#include "stdafx.h"
#include "Material.h"

using namespace Crystal::Graphics;

Imagef Texture::toImagef() const
{
	if (filename.empty()) {
		Imagef image(1, 1);
		image.setColor(0, 0, ColorRGBA<float>(1.0, 1.0, 1.0, 1.0));
		return image;
	}
	else {
		Imagef image(filename);
		return image;
	}
}

Material::Material(const unsigned int id) :
	diffuse(Graphics::ColorRGBA<float>::Black()),
	specular(Graphics::ColorRGBA<float>::Black()),
	ambient(Graphics::ColorRGBA<float>::Black()),
	shininess(1.0f),
	transparent(0.0f),
	id(id)
{
}
