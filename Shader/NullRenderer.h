#ifndef __CRYSTAL_SHADER_NULL_RENDERER_H__
#define __CRYSTAL_SHADER_NULL_RENDERER_H__

#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

template<typename GeomType, typename ValueType, typename ColorType>
class NullRenderer : public IRenderer<GeomType>
{
public:
	NullRenderer() = default;

	~NullRenderer() = default;

	void render(const int width, const int height, const Graphics::ICamera<float>& camera) override {};
};

	}
}

#endif