#ifndef __CRYSTAL_SHADER_DEPTH_RENDERER_H__
#define __CRYSTAL_SHADER_DEPTH_RENDERER_H__

#include "IDRenderer.h"

namespace Crystal {
	namespace Shader {



class DepthRenderer : public IRenderer<float>
{
public:
	void render(const Graphics::ICamera<float>& camera);

	void findLocation() override {};
};
	}
}

#endif