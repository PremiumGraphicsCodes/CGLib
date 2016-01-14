#ifndef __CRYSTAL_SHADER_SMOOTH_RENDERER_H__
#define __CRYSTAL_SHADER_SMOOTH_RENDERER_H__

#include <map>
#include <vector>

#include "../Shader/ShaderObject.h"

#include "../Graphics/TriangleBuffer.h"

#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

template<typename GeomType>
class SmoothRenderer final : public IRenderer<GeomType>
{
public:

	SmoothRenderer() = default;

	~SmoothRenderer() = default;

	void findLocation() override;

	void setBuffer(const Graphics::TriangleBuffer& buffer) { this->buffer = buffer; }

	void render(const Graphics::ICamera<float>& camera) override;

private:
	Graphics::TriangleBuffer buffer;
};


	}
}

#endif