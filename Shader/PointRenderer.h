#ifndef __CRYSTAL_POINT_RENDERER_H__
#define __CRYSTAL_POINT_RENDERER_H__

#include "../Graphics/ICamera.h"
#include "../Graphics/PointBuffer.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

template<typename GeomType>
class PointRenderer
{
public:
	PointRenderer(ShaderObject& shader) :
		shader(shader)
	{}

	~PointRenderer() = default;

	void findLocation();

	void render(const Graphics::ICamera<float>& camera, const Graphics::PointBuffer& buffer);

	//void changeSize(const float size) { this->pointSize = size; }

private:
	ShaderObject& shader;
};

	}
}

#endif