#ifndef __CRYSTAL_SHADER_LINE_RENDERER_H__
#define __CRYSTAL_SHADER_LINE_RENDERER_H__

#include <map>
#include <vector>

#include "ShaderObject.h"
#include "../Util/UnCopyable.h"

#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

template<typename GeomType>
class LineRenderer final : public IRenderer
{
public:
	struct {
		std::vector<float> positions;
		std::vector<float> colors;
	};

	LineRenderer() = default;

	LineRenderer(const ShaderObject& shader) :
		IRenderer(shader)
	{}

	~LineRenderer() = default;

	void findLocation() override;

	void render(const Graphics::ICamera<GeomType>& camera) override;

private:

};

	}
}

#endif