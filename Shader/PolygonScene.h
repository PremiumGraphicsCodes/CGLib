#ifndef __CRYSTAL_SHADER_POLYGON_SCENE__
#define __CRYSTAL_SHADER_POLYGON_SCENE__

#include "../Util/UnCopyable.h"

#include "../Graphics/VisualPolygon.h"
#include "../Shader/TextureObject.h"
#include "SmoothRenderer.h"

namespace Crystal {
	namespace Shader {

class PolygonScene : private UnCopyable
{
public:
	PolygonScene() = default;

	explicit PolygonScene(const Graphics::VisualPolygon& vp);

	void setup(const Graphics::VisualPolygon& vp);

	void draw(const Graphics::ICamera<float>& camera, const Graphics::PointLight<float>& light);

private:
	Graphics::TriangleBuffer triangleBuffer;
	std::vector<VisualMaterial> materials;
	SmoothRenderer renderer;
};
	}
}

#endif