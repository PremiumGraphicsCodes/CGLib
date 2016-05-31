#ifndef __CRYSTAL_SHADER_ACTOR_SCENE__
#define __CRYSTAL_SHADER_ACTOR_SCENE__

#include "../Util/UnCopyable.h"

#include "../Core/Actor.h"
#include "../Graphics/VisualPolygon.h"
#include "../Shader/TextureObject.h"
#include "SmoothRenderer.h"

namespace Crystal {
	namespace Shader {

class ActorScene : private UnCopyable
{
public:
	ActorScene() = default;

	explicit ActorScene(const Core::Actor& actor);

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