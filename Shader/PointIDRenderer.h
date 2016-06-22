#ifndef __CRYSTAL_SHADER_POINT_ID_RENDERER_H__
#define __CRYSTAL_SHADER_POINT_ID_RENDERER_H__

#include "IRenderer.h"
#include "../Graphics/PointIdBuffer.h"
#include "../Graphics/LineBuffer.h"
#include "../Graphics/TriangleBuffer.h"

namespace Crystal {
	namespace Shader {

class PointIDRenderer
{
public:
	PointIDRenderer() = default;

	~PointIDRenderer() = default;

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