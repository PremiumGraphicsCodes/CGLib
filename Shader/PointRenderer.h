#ifndef __CRYSTAL_POINT_RENDERER_H__
#define __CRYSTAL_POINT_RENDERER_H__

#include "../Graphics/ICamera.h"
#include "../Graphics/PointBuffer.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

template<typename GeomType>
class PointRenderer final : public IRenderer<GeomType>
{
public:
	PointRenderer()
	{}

	PointRenderer(const ShaderObject& shader) :
		IRenderer(shader)
	{}

	~PointRenderer() = default;

	void findLocation() override;

	void setBuffer(const Graphics::PointBuffer& b) { this->buffers = b.getBuffers(); }

	void render(const Graphics::ICamera<float>& camera) override;

	//void changeSize(const float size) { this->pointSize = size; }

};

	}
}

#endif