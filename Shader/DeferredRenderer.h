#ifndef __CRYSTAL_SHADER_DEFERRED_RENDERER_H__
#define __CRYSTAL_SHADER_DEFERRED_RENDERER_H__

#include "../Graphics/ICamera.h"
#include "../Graphics/PointBuffer.h"
#include "Texture.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

class DeferredRenderer
{
public:
	void render(const Texture<unsigned char>& depthTexture);

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