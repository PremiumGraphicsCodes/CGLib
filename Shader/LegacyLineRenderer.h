#ifndef __CRYSTAL_UI_LEGACY_LINE_RENDERER_H__
#define __CRYSTAL_UI_LEGACY_LINE_RENDERER_H__

#include "GLee.h"

#include "../Math/Line3d.h"

#include "../Graphics/ICamera.h"
#include "../Graphics/LineBuffer.h"

#include "../Graphics/Buffer3d.h"
#include "../Graphics/Buffer4d.h"

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
