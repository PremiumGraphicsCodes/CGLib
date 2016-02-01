#ifndef __CRYSTAL_UI_LEGACY_LINE_RENDERER_H__
#define __CRYSTAL_UI_LEGACY_LINE_RENDERER_H__

#include "GLee.h"
#include "../Graphics/ICamera.h"

#include "../Graphics/Buffer3d.h"
#include "../Graphics/Buffer4d.h"

namespace Crystal {
	namespace Shader {

struct LineBuffer
{
	Graphics::Buffer3d<float> position;
	Graphics::Buffer4d<float> color;
	std::vector<unsigned int> indices;
};


class LegacyLineRenderer
{
public:

	void render(const Graphics::ICamera<float>& camera, const LineBuffer& buffer);

};
	}
}


#endif // ! __CRYSTAL_UI_LEGACY_LINE_RENDERER_H__
