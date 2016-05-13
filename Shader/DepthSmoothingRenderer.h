#ifndef __CRYSTAL_SHADER_DEPTH_SMOOTHING_RENDERER_H__
#define __CRYSTAL_SHADER_DEPTH_SMOOTHING_RENDERER_H__

#include "../Graphics/ICamera.h"
#include "../Graphics/PointBuffer.h"
#include "TextureObject.h"
#include "DepthTexture.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

class DepthSmoothingRenderer
{
public:
	void render(const ITextureObject& texture, bool isX);

	bool build();

private:
	std::string getBuildinVertexShaderSource();

	std::string getBuildinFragmentShaderSource();

	void findLocation();


private:
	ShaderObject shader;
	ShaderUnit vertexShader;
	ShaderUnit fragmentShader;
};

	}
}

#endif