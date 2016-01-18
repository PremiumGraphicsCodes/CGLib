#ifndef __CRYSTAL_UI_LEGACY_SURFACE_RENDERER_H__
#define __CRYSTAL_UI_LEGACY_SURFACE_RENDERER_H__

#include "GLee.h"
#include "../Graphics/ICamera.h"
#include "../Graphics/Surface.h"

namespace Crystal {
	namespace Shader {

class LegacySurfaceRenderer
{
public:

	void render(const Graphics::ICamera<float>& camera, const Graphics::Surface<float>& surface);

};
	}
}


#endif