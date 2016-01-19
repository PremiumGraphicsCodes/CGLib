#ifndef __CRYSTAL_UI_LEGACY_LINE_RENDERER_H__
#define __CRYSTAL_UI_LEGACY_LINE_RENDERER_H__

#include "GLee.h"
#include "../Graphics/ICamera.h"
#include "../Graphics/Surface.h"
#include "../Graphics/LineBuffer.h"

namespace Crystal {
	namespace Shader {

class LegacyLineRenderer
{
public:

	void render(const Graphics::ICamera<float>& camera, const Graphics::LineBuffer& buffer);

};
	}
}


#endif // ! __CRYSTAL_UI_LEGACY_LINE_RENDERER_H__
