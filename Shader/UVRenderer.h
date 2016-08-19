#ifndef __CRYSTAL_SHADER_UV_RENDERER_H__
#define __CRYSTAL_SHADER_UV_RENDERER_H__

#include <map>
#include <vector>

#include "../Shader/ShaderObject.h"

#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

class UVRenderer
{
public:
	UVRenderer() = default;

	~UVRenderer() = default;

	void set(ShaderObject* shader);

	void render(const Graphics::ICamera<float>& camera, const Graphics::TriangleBuffer& buffer);

	bool build();

private:

	static std::string getBuildinVertexShaderSource();

	static std::string getBuildinFragmentShaderSource();

	ShaderObject* shader;
};


	}
}

#endif