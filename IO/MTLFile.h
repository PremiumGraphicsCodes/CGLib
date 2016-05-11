#ifndef __CRYSTAL_IO_MTL_FILE_H__
#define __CRYSTAL_IO_MTL_FILE_H__

#include <map>

#include "../Graphics/Material.h"
#include "../Graphics/ColorRGBA.h"

#include "../Math/Vector3d.h"


#include <cassert>

#include <fstream>
#include <string>

namespace Crystal {
	namespace IO {

struct OBJMaterial {
	enum Illumination {
		COLOR_ON_AND_AMBIENT_OFF = 0,
		COLOR_ON_AND_AMBIENT_ON = 1,
		HIGHLIGHT_ON = 2,
		REFRECTION_ON_AND_RAY_TRACE_ON = 3,

		REFLECTION_ON_AND_RAY_TRACE_OFF = 8,

		CAST_SHADOWS_ONTO_INVISIBLE_SURFACES = 10,
	};

	OBJMaterial();

	bool read(std::istream& stream);

	bool write(std::ostream& stream) const;

	void setName(const std::string& name) { this->name = name; }

	std::string getName() const { return name; }

	void setAmbient(const Graphics::ColorRGBA<float>& a) { this->ambient = a; }

	Graphics::ColorRGBA<float> getAmbient() const { return ambient; }

	void setDiffuse(const Graphics::ColorRGBA<float>& d) { this->diffuse = d; }

	Graphics::ColorRGBA<float> getDiffuse() const { return diffuse; }

	void setSpecular(const Graphics::ColorRGBA<float>& s) { this->specular = s; }

	void setSpecularExponent(const float f) { this->specularExponent = f; }

	float getSpecularExponent() const { return specularExponent; }

	Graphics::ColorRGBA<float> getSpecular() const { return specular; }

	void setIllumination(const Illumination& i) { this->illumination = i; }

	Illumination getIllumination() const { return illumination; }

	void setAmbientTextureName(const std::string& tname) { this->ambientTexture = tname; }

	std::string getAmbientTextureName() const { return ambientTexture; }

	void setDiffuseTextureName(const std::string& dname) { this->diffuseTexture = dname; }

	std::string getDiffuseTextureName() const { return diffuseTexture; }

	void setShininessTextureName(const std::string sname) { this->shininessTexture = sname; }

	std::string getShininessTextureName() const { return shininessTexture; }

	void setBumpTextureName(const std::string& bname) { this->bumpTexture = bname; }

	std::string getBumpTextureName() const { return bumpTexture; }

	void setTransparent(const float t) { this->transparent = t; }

	float getTransparent() const { return transparent; }

	void setOpticalDensity(const float d) {
		assert( ( 0.001f <= d ) && (d <= 10.0f) );
		this->opticalDensity = d;
	}

	float getOpticalDensity() const { return opticalDensity; }

	bool operator==(const OBJMaterial& rhs) const {
		return
			name == rhs.name &&
			ambient == rhs.ambient &&
			diffuse == rhs.diffuse &&
			specular == rhs.specular &&
			ambientTexture == rhs.ambientTexture &&
			diffuseTexture == rhs.diffuseTexture &&
			bumpTexture == rhs.bumpTexture &&
			shininessTexture == rhs.shininessTexture &&
			illumination == rhs.illumination;
	}

	Graphics::Material toMaterial(const std::string& directory) const;


private:
	std::string name;
	Graphics::ColorRGBA<float> ambient;
	Graphics::ColorRGBA<float> diffuse;
	Graphics::ColorRGBA<float> specular;
	Illumination illumination;
	std::string ambientTexture;
	std::string diffuseTexture;
	std::string shininessTexture;
	std::string bumpTexture;
	float specularExponent;
	float transparent;
	float opticalDensity;
};

class MTLFile
{
public:

	bool read(const std::string& filename);

	bool read(std::istream& stream);

	bool write(const std::string& filename);

	bool write(std::ostream& stream);

	OBJMaterial find(const std::string& name) {
		for (const auto& m : materials) {
			if (m.getName() == name) {
				return m;
			}
		}
		assert(false);
		return OBJMaterial();
	}

	std::vector<OBJMaterial> materials;
	//MTLTextureOption option;
};


	}
}

#endif