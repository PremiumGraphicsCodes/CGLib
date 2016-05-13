#ifndef __CRYSTAL_SHADER_SKY_BOX_RENDERER_H__
#define __CRYSTAL_SHADER_SKY_BOX_RENDERER_H__

#include "../Graphics/ICamera.h"
#include "../Graphics/TriangleBuffer.h"
#include "../Graphics/Light.h"
#include "../Graphics/Material.h"
#include "CubeMapTextureObject.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

class SkyBoxRenderer
{
public:
	void render(const CubeMapTextureObject& cubeMapTexture, const Graphics::ICamera<float>& camera);

	bool build();

private:
	std::string getBuiltinVertexShaderSource();

	std::string getBuiltinFragmentShaderSource();

	void findLocation();

private:
	ShaderObject shader;
};

	}
}


#endif