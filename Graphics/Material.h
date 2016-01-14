#ifndef __CRYSTAL_GRAPHICS_MATERIAL_H__
#define __CRYSTAL_GRAPHICS_MATERIAL_H__

#include <list>
#include <string>
#include <memory>

#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

struct Texture
{
	std::string ambient;
	std::string diffuse;
	std::string bump;
	std::string shininess;
};

class Material
{
public:

	/*
	Material() :
		diffuse(Graphics::ColorRGBA<float>::Black()),
		specular(Graphics::ColorRGBA<float>::Black()),
		ambient(Graphics::ColorRGBA<float>::Black()),
		shininess(1.0f),
		id(id)
	{
	}
	*/


	Material(const unsigned int id) :
		diffuse( Graphics::ColorRGBA<float>::Black() ),
		specular( Graphics::ColorRGBA<float>::Black() ),
		ambient( Graphics::ColorRGBA<float>::Black() ),
		shininess( 1.0f ),
		transparent( 0.0f ),
		id( id )
	{
	}

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

	void setTexture(const Texture& texture) { this->texture = texture; }

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

class MaterialBuilder
{
public:
	MaterialBuilder() :
		nextId(0)
	{}

	~MaterialBuilder()
	{
		clear();
	}

	Material* build(){
		Material* m(new Material(nextId++));
		materials.push_back(m);
		return m;
	};

	std::list< Material* > getMaterials() const { return materials; }

	void clear() {
		for (Material* m : materials) {
			delete m;
		}
		materials.clear();
	}

private:
	unsigned int nextId;
	std::list< Material* > materials;
};

	}
}


#endif