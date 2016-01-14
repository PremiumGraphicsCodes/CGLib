#ifndef __CRYSTAL_SHADER_QUAD_RENDERER_H__
#define __CRYSTAL_SHADER_QUAD_RENDERER_H__

#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

template<typename GeomType>
class QuadRenderer : public IRenderer<GeomType>
{
public:
	QuadRenderer() = default;

	QuadRenderer(const ShaderObject& shader) :
		IRenderer(shader)
	{}

	~QuadRenderer() = default;

	void findLocation() override;

	void render(const Graphics::ICamera<GeomType>& camera) override;

private:
};
	}
}

#endif
