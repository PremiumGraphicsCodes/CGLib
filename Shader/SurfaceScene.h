#ifndef __CRYSTAL_SHADER_SURFACE_SCENE__
#define __CRYSTAL_SHADER_SURFACE_SCENE__

#include "../Util/UnCopyable.h"

#include "../Graphics/VisualSurface.h"
#include "SmoothRenderer.h"

namespace Crystal {
	namespace Shader {

class SurfaceScene : private UnCopyable
{
public:
	SurfaceScene() = default;

	explicit SurfaceScene(const Graphics::VisualSurface& vs);

	void setup(const Graphics::VisualSurface& vp);

	void draw(const Graphics::ICamera<float>& camera, const Graphics::PointLight<float>& light);

private:
	Graphics::TriangleBuffer triangleBuffer;
	std::vector<VisualMaterial> materials;
	SmoothRenderer renderer;
};

	}
}

#endif