#ifndef __CRYSTAL_SHADER_DEPTH_RENDERER_H__
#define __CRYSTAL_SHADER_DEPTH_RENDERER_H__

#include "IDRenderer.h"

namespace Crystal {
	namespace Shader {

class DepthRenderer
{
public:
	void render(const Graphics::ICamera<float>& camera,const Graphics::TriangleBuffer& buffer);

	bool build();
private:
	ShaderObject shader;

	std::string getBuiltinVertexShaderSource();

	std::string getBuiltinFragmentShaderSource();

	void findLocation();

};
	}
}

#endif