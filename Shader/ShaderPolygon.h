#ifndef __CRYSTAL_SHADER_SHADER_POLYGON__
#define __CRYSTAL_SHADER_SHADER_POLYGON__

#include "../Util/UnCopyable.h"

#include "../Graphics/VisualPolygon.h"
#include "SmoothRenderer.h"

namespace Crystal {
	namespace Shader {

class ShaderPolygon : private UnCopyable
{
public:
	ShaderPolygon() = default;

	explicit ShaderPolygon(const Graphics::VisualPolygon& vp);

	void setup(const Graphics::VisualPolygon& vp);

	void draw(const Graphics::ICamera<float>& camera, const Graphics::PointLight<float>& light);

private:
	Graphics::TriangleBuffer triangleBuffer;
	std::vector<Graphics::MaterialMap> materialMaps;
	SmoothRenderer renderer;
};
	}
}

#endif