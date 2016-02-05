#ifndef __CRYSTAL_SHADER_LEGACY_POINT_RENDERER_H__
#define __CRYSTAL_SHADER_LEGACY_POINT_RENDERER_H__

#include "GLee.h"

#include "../Graphics/PointBuffer.h"
#include "../Graphics/ICamera.h"

namespace Crystal {
	namespace Shader {

class LegacyPointRenderer
{
public:
	void render(Graphics::ICamera<float>& camera, const Graphics::PointBuffer& buffer);

private:

};

	}
}

#endif