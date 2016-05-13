#ifndef __CRYSTAL_SHADER_NORMAL_FILTER_H__
#define __CRYSTAL_SHADER_NORMAL_FILTER_H__

#include "../Graphics/ICamera.h"
#include "../Graphics/PointBuffer.h"
#include "Texture.h"
#include "DepthTexture.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

class NormalFilter
{
public:
	void render(const ITextureObject& texture, const Graphics::ICamera<float>& renderedCamera);

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