#include "stdafx.h"
#include "Material.h"
#include "Texture.h"

using namespace Crystal::Graphics;


Material::Material(const unsigned int id) :
	diffuse(Graphics::ColorRGBA<float>::Black()),
	specular(Graphics::ColorRGBA<float>::Black()),
	ambient(Graphics::ColorRGBA<float>::Black()),
	shininess(1.0f),
	transparent(0.0f),
	id(id),
	texture(nullptr)
{
}
