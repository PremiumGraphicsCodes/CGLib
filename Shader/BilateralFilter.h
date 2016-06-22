#ifndef __CRYSTAL_SHADER_BILATERAL_FILTER_H__
#define __CRYSTAL_SHADER_BILATERAL_FILTER_H__

#include "TextureObject.h"
#include "DepthTextureObject.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

class BilateralFilter
{
public:
	void render(const ITextureObject& texture);

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