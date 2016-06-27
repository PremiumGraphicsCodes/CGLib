#ifndef __CRYSTAL_SHADER_POINT_ID_RENDERER_H__
#define __CRYSTAL_SHADER_POINT_ID_RENDERER_H__

#include "IRenderer.h"
#include "../Graphics/PointIdBuffer.h"

namespace Crystal {
	namespace Shader {

class PointIdRenderer
{
public:
	PointIdRenderer() = default;

	~PointIdRenderer() = default;

	void set(ShaderObject* shader);

	void render(const Graphics::ICamera<float>& camera, const Graphics::PointIdBuffer& buffer);

	bool build();

private:
	std::string getBuildinVertexShaderSource() const;

	std::string getBuildinFragmentShaderSource() const;

	ShaderObject* shader;

};
	}
}

#endif