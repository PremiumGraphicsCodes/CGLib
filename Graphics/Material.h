#ifndef __CRYSTAL_GRAPHICS_MATERIAL_H__
#define __CRYSTAL_GRAPHICS_MATERIAL_H__

#include <list>
#include <string>
#include <memory>

#include "ColorRGBA.h"
#include "Texture.h"

namespace Crystal {
	namespace Graphics {


class Material
{
public:

	Material(const unsigned int id = 0);

	~Material()
	{}

public:

	std::string getName() const { return name;  }

	void setName(const std::string& name) { this->name = name; }

	void setAmbient( const Graphics::ColorRGBA<float>& a ) { this->ambient = a; }

	Graphics::ColorRGBA<float> getAmbient() const { return ambient; }

	void setDiffuse( const Graphics::ColorRGBA<float>& d ) { this->diffuse = d; }

	Graphics::ColorRGBA<float> getDiffuse() const { return diffuse; }

	void setSpecular( const Graphics::ColorRGBA<float>& s ) { this->specular = s; }

	Graphics::ColorRGBA<float> getSpecular() const { return specular; }

	void setShininess( const float s ) { this->shininess = s; }

	float getShininess() const { return shininess; }

	void setTransparent(const float t) { this->transparent = t; }

	float getTransparent() const { return transparent; }

	Texture getTexture() const { return texture; }

	void setTexture(const Texture textures) { this->texture = texture; }

	unsigned int getId() const { return id; }

private:
	std::string name;

	float shininess;
	float transparent;
	Graphics::ColorRGBA<float> ambient;
	Graphics::ColorRGBA<float> diffuse;
	Graphics::ColorRGBA<float> specular;

	const unsigned int id;

	Texture texture;
};

using PolygonMaterialMap = std::map<Core::PolygonMesh*, Material*>;

	}
}


#endif