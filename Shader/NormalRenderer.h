#ifndef __CRYSTAL_SHADER_NORMAL_RENDERER_H__
#define __CRYSTAL_SHADER_NORMAL_RENDERER_H__

#include <map>
#include <vector>

#include "ShaderObject.h"

#include "../Graphics/ICamera.h"

#include "IRenderer.h"

#include <memory>

namespace Crystal {
	namespace Shader {

template<typename GeomType>
class NormalRenderer : public IRenderer<GeomType>{
public:

	NormalRenderer() : scale(1)
	{}

	NormalRenderer(const ShaderObject& shader) :
		IRenderer(shader)
	{}

	~NormalRenderer() = default;

	void findLocation() override {}

	void render(const Graphics::ICamera<GeomType>& camera);

	float scale;
};

	}
}

#endif