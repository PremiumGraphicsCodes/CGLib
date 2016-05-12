#ifndef __CRYSTAL_SHADER_VISUAL_MATERIAL_H__
#define __CRYSTAL_SHADER_VISUAL_MATERIAL_H__

#include <array>
#include "Texture.h"

namespace Crystal {
	namespace Graphics {
		class Material;
		class MaterialMap;
	}
	namespace Shader {

class VisualMaterial
{
public:
	VisualMaterial() = default;

	VisualMaterial(const Graphics::MaterialMap& material);

	bool load(const Graphics::MaterialMap& material);

	std::array<float, 3> getDiffuseColor() const { return diffuseColor; }

	std::array<float, 3> getSpecularColor() const { return specularColor; }

	std::array<float, 3> getAmbientColor() const { return ambientColor; }

	int getStartFaceIndex() const { return startFaceIndex; }

	int getEndFaceIndex() const { return endFaceIndex; }

	float getShininess() const { return shininess; }

	Texturef getDiffuseTex() const { return diffuseTex; }

private:
	int startFaceIndex;
	int endFaceIndex;
	Texturef diffuseTex;
	std::array<float, 3> diffuseColor;
	std::array<float, 3> specularColor;
	std::array<float, 3> ambientColor;
	float shininess;
};
	}
}

#endif