#ifndef __CRYSTAL_SHADER_SS_COMPOSITE_RENDERER_H__
#define __CRYSTAL_SHADER_SS_COMPOSITE_RENDERER_H__

#include "../Graphics/ICamera.h"
#include "../Graphics/PointBuffer.h"
#include "TextureObject.h"
#include "DepthTextureObject.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

class SSCompositeRenderer
{
public:
	void render(const ITextureObject& texture, const ITextureObject& texture2, const DepthTextureObject& depthTexture1, const ITextureObject& depthTexture2);

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