#ifndef __CRYSTAL_IO_MTL_FILE_H__
#define __CRYSTAL_IO_MTL_FILE_H__

#include <map>

#include "../Graphics/Material.h"
#include "../Graphics/ColorRGB.h"

#include "../Math/Vector3d.h"


#include <cassert>

#include <fstream>
#include <string>

namespace Crystal {
	namespace IO {

struct MTLTextureOption {

	MTLTextureOption()
	{
		setDefault();
	}

	void setDefault();

	void setBlendU(const bool u) { this->blendu = u; }

	bool getBlendU() const { return blendu; }

	void setBlendV(const bool v) { this->blendv = v; }

	bool getBlendV() const { return blendv; }

	void setBoost(const float b) { this->boost = b; }

	float getBoost() const { return boost; }

	void setBaseValue(const float v) { this->baseValue = v; }

	float getBaseValue() const { return baseValue; }

	void setGainValue(const float v) { this->gainValue = v; }

	float getGainValue() const { return gainValue; }

	void setOrigin(const Math::Vector3d<float>& origin) { this->origin = origin; }

	Math::Vector3d<float> getOrigin() const { return origin; }

	void setScale(const Math::Vector3d<float>& scale) { this->scale = scale; }

	Math::Vector3d<float> getScale() const { return scale; }

	void setTurblence(const Math::Vector3d<float>& t) { this->turblence = t; }

	Math::Vector3d<float> getTurblence() const { return turblence; }

	void setResolution(const int resolution) { this->resolution = resolution; }

	int getResolution() const { return resolution; }

	void setClamp(const bool clamp) { this->clamp = clamp; }

	bool getClamp() const { return clamp; }

	void setBumpMultiplier(const float bm) { this->bm = bm; }

	float getBumpMultiplier() const { return bm; }

	void setImfChan(const std::string& imf) { this->imfchan = imf; }

	std::string getImfChan() const { return imfchan; }

	void setType(const std::string& type) { this->type = type; }

	std::string getType() const { return type; }

private:
	bool blendu;
	bool blendv;
	float boost;
	float baseValue;
	float gainValue;
	Math::Vector3d<float> origin;
	Math::Vector3d<float> scale;
	Math::Vector3d<float> turblence;
	int resolution;
	bool clamp;
	float bm;
	std::string imfchan;
	std::string type;
};


struct MTL {
	enum Illumination {
		COLOR_ON_AND_AMBIENT_OFF = 0,
		COLOR_ON_AND_AMBIENT_ON = 1,
		HIGHLIGHT_ON = 2,
		REFRECTION_ON_AND_RAY_TRACE_ON = 3,

		REFLECTION_ON_AND_RAY_TRACE_OFF = 8,

		CAST_SHADOWS_ONTO_INVISIBLE_SURFACES = 10,
	};

	MTL()
	{
		illumination = Illumination::COLOR_ON_AND_AMBIENT_OFF;
	}

	void setName(const std::string& name) { this->name = name; }

	std::string getName() const { return name; }

	void setAmbient(const Graphics::ColorRGB<float>& a) { this->ambient = a; }

	Graphics::ColorRGB<float> getAmbient() const { return ambient; }

	void setDiffuse(const Graphics::ColorRGB<float>& d) { this->diffuse = d; }

	Graphics::ColorRGB<float> getDiffuse() const { return diffuse; }

	void setSpecular(const Graphics::ColorRGB<float>& s) { this->specular = s; }

	void setSpecularExponent(const float f) { this->specularExponent = f; }

	float getSpecularExponent() const { return specularExponent; }

	Graphics::ColorRGB<float> getSpecular() const { return specular; }

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

	bool operator==(const MTL& rhs) const {
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

private:
	std::string name;
	Graphics::ColorRGB<float> ambient;
	Graphics::ColorRGB<float> diffuse;
	Graphics::ColorRGB<float> specular;
	Illumination illumination;
	std::string ambientTexture;
	std::string diffuseTexture;
	std::string shininessTexture;
	std::string bumpTexture;
	float specularExponent;
	float transparent;
	float opticalDensity;
};

class MTLFile {
public:


	static MTLTextureOption getTextureOptions(const std::string& str);

	static std::vector< std::string > writeTextureOptions(std::ostream& stream, MTLTextureOption& option);

	static bool readOnOff(const std::string& str)
	{
		if (str == "on") {
			return true;
		}
		else if (str == "off") {
			return false;
		}
		else {
			assert(false);
			return false;
		}
	}

	std::vector<MTL> mtls;
	MTLTextureOption option;
};

class MTLFileReader
{
public:

	MTLFile read(const std::string& filename);

	MTLFile read(std::istream& stream);
};

class MTLFileWriter
{
public:
	bool save(const std::string& filename, const Graphics::Material& m);

	bool save(std::ostream& stream, const Graphics::Material& m);

	std::vector< std::string > getStrs() const { return strs; }

private:
	std::vector< std::string > strs;
};

	}
}

#endif