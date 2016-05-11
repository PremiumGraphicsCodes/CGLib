#ifndef __CRYSTAL_GRAPHICS_MATERIAL_H__
#define __CRYSTAL_GRAPHICS_MATERIAL_H__

#include <list>
#include <string>
#include <memory>

#include "Image.h"
#include "ColorRGBA.h"

namespace Crystal {
	namespace Graphics {

class Texture
{
public:
	Texture() = default;

	Texture(const std::string& filename) { this->filename = filename; }

	void setDirectory(const std::string& str) { filename = str + "\\" + filename; }

	bool hasFileName() const { return filename.empty(); }

	void setFileName(const std::string& filename) { this->filename = filename; }

	Imagef toImagef() const;

private:
	std::string filename;
};

class Textures
{
public:
	void setDirectory(const std::string& directory) {
		ambient.setDirectory(directory);
		diffuse.setDirectory(directory);
		bump.setDirectory(directory);
	}

	void setAmbient(const Texture& t) { this->ambient = t; }

	void setDiffuse(const Texture& t) { this->diffuse = t; }

	void setBump(const Texture& t) { this->bump = t; }

	Texture getAmbient() const { return ambient; }

	Texture getDiffuse() const { return diffuse; }

	Texture getBump() const { return bump; }

private:
	Texture ambient;
	Texture diffuse;
	Texture bump;
};

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

	Textures getTextures() const { return textures; }

	void setTextures(const Textures& textures) { this->textures = textures; }

	unsigned int getId() const { return id; }

private:
	std::string name;

	float shininess;
	float transparent;
	Graphics::ColorRGBA<float> ambient;
	Graphics::ColorRGBA<float> diffuse;
	Graphics::ColorRGBA<float> specular;

	const unsigned int id;

	Textures textures;
};
	}
}


#endif