#ifndef __CRYSTAL_SHADER_NORMAL_FILTER_H__
#define __CRYSTAL_SHADER_NORMAL_FILTER_H__

#include "../Graphics/ICamera.h"
#include "../Graphics/PointBuffer.h"
#include "Texture.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

class NormalFilter
{
public:
	void render(const Texture<float>& texture);

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