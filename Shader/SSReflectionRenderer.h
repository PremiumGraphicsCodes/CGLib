#ifndef __CRYSTAL_SS_REFLECTION_RENDERER_H__
#define __CRYSTAL_SS_REFLECTION_RENDERER_H__

#include "../Graphics/ICamera.h"
#include "../Graphics/PointBuffer.h"
#include "../Graphics/Light.h"
#include "../Graphics/Material.h"
#include "Texture.h"
#include "DepthTexture.h"
#include "CubeMapTexture.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

class SSReflectionRenderer
{
public:
	void render(const ITexture& depthTexture, const ITexture& normalTexture, const Graphics::ICamera<float>& renderedCamera, const CubeMapTexture& cubeMapTexture);

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