#ifndef __CRYSTAL_SHADER_SS_NORMAL_RENDERER_H__
#define __CRYSTAL_SHADER_SS_NORMAL_RENDERER_H__

#include "FrameBuffer.h"
#include "DepthBuffer.h"
#include "ShaderObject.h"
#include "../Graphics/TriangleBuffer.h"
#include "../Graphics/ICamera.h"

namespace Crystal {
	namespace Shader {

class SSNormalRenderer
{
public:
	void build(const int width, const int height);

	void render(const int width, const int height, const Crystal::Graphics::ICamera<float>& camera, const Crystal::Graphics::TriangleBuffer& buffer);

private:
	std::string getBuiltinVertexShaderSource();

	std::string getBuiltinFragmentShaderSource();

	void findLocation();

	ShaderObject shader;
};

	}
}

#endif