#ifndef __CRYSTAL_SHADER_SS_COMPOSITE_RENDERER_H__
#define __CRYSTAL_SHADER_SS_COMPOSITE_RENDERER_H__

#include "../Graphics/ICamera.h"
#include "../Graphics/PointBuffer.h"
#include "Texture.h"
#include "DepthTexture.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

class SSCompositeRenderer
{
public:
	void render(const ITexture& texture, const ITexture& texture2, const DepthTexture& depthTexture1, const DepthTexture& depthTexture2);

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