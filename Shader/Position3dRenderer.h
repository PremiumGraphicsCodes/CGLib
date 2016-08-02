#ifndef __CRYSTAL_SHADER_POSITION_3D_RENDERER_H__
#define __CRYSTAL_SHADER_POSITION_3D_RENDERER_H__

#include "DepthTextureObject.h"
#include "TextureObject.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

class Position3dRenderer
{
public:
	void render(const ITextureObject& depthTexture, const Graphics::ICamera<float>& renderedCamera);

	bool build();

private:
	std::string getBuildinVertexShaderSource();

	std::string getBuildinFragmentShaderSource();

	void findLocation();

private:
	ShaderObject shader;
};

	}
}

#endif