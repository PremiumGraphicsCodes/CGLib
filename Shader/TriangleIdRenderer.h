#ifndef __CRYSTAL_SHADER_TRIANGLE_ID_RENDERER_H__
#define __CRYSTAL_SHADER_TRIANGLE_ID_RENDERER_H__

#include "IRenderer.h"
#include "../Graphics/TriangleIdBuffer.h"

namespace Crystal {
	namespace Shader {

class TriangleIdRenderer
{
public:
	TriangleIdRenderer() = default;

	~TriangleIdRenderer() = default;

	void set(ShaderObject* shader);

	void render(const Graphics::ICamera<float>& camera, const Graphics::TriangleIdBuffer& buffer);

	bool build();

private:
	std::string getBuildinVertexShaderSource() const;

	std::string getBuildinFragmentShaderSource() const;

	ShaderObject* shader;

};
	}
}

#endif