#ifndef __CRYSTAL_UI_LEGACY_LINE_RENDERER_H__
#define __CRYSTAL_UI_LEGACY_LINE_RENDERER_H__

#include "GLee.h"

#include "../Math/Line3d.h"

#include "../Graphics/ICamera.h"

#include "../Graphics/Buffer3d.h"
#include "../Graphics/Buffer4d.h"

namespace Crystal {
	namespace Shader {

struct LineBuffer
{
	LineBuffer() :
		nextId(0)
	{
	}

	void add(const Math::Line3d<float>& line, const Graphics::ColorRGBA<float>& c) {
		position.add(line.getStart());
		position.add(line.getEnd());
		color.add(c);
		color.add(c);
		indices.push_back(nextId++);
		indices.push_back(nextId++);
	}

	Graphics::Buffer3d<float> position;
	Graphics::Buffer4d<float> color;
	std::vector<unsigned int> indices;

private:
	unsigned int nextId;
};


class LegacyLineRenderer
{
public:

	void render(const Graphics::ICamera<float>& camera, const LineBuffer& buffer);

};
	}
}


#endif // ! __CRYSTAL_UI_LEGACY_LINE_RENDERER_H__
