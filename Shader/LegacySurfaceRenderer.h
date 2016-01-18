#ifndef __CRYSTAL_UI_LEGACY_SURFACE_RENDERER_H__
#define __CRYSTAL_UI_LEGACY_SURFACE_RENDERER_H__

#include "GLee.h"
#include "../Graphics/ICamera.h"
#include "../Graphics/Light.h"
#include "../Graphics/Surface.h"
#include "../Graphics/TriangleBuffer.h"

namespace Crystal {
	namespace Shader {

class LegacySurfaceRenderer
{
public:

	void render(const Graphics::ICamera<float>& camera, const Graphics::PointLight<float>& light, const Graphics::TriangleBuffer& buffer);

};
	}
}


#endif