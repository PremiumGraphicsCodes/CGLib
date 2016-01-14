#ifndef __CRYSTAL_SHADER_LINE_RENDERER_H__
#define __CRYSTAL_SHADER_LINE_RENDERER_H__

#include <map>
#include <vector>

#include "ShaderObject.h"
#include "../Util/UnCopyable.h"

#include "IRenderer.h"
#include "../Graphics/LineBuffer.h"

namespace Crystal {
	namespace Shader {

template<typename GeomType>
class LineRenderer final : public IRenderer<GeomType>
{
public:
	LineRenderer() = default;

	LineRenderer(const ShaderObject& shader) :
		IRenderer(shader)
	{}

	~LineRenderer() = default;

	void setBuffer(const Graphics::LineBuffer& b) { this->buffers = b.getBuffers(); }

	void findLocation() override;

	void render(const Graphics::ICamera<GeomType>& camera) override;

private:

};

	}
}

#endif