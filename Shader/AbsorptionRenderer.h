#ifndef __CRYSTAL_SHADER_ABSORPTION_RENDERER_H__
#define __CRYSTAL_SHADER_ABSORPTION_RENDERER_H__

#include "../Graphics/ICamera.h"
#include "../Graphics/PointBuffer.h"
#include "Texture.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

class AbsorptionRenderer
{
public:
	void render(const ITexture& volumeTexture);

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