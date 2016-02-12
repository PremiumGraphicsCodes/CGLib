#ifndef __CRYSTAL_SHADER_LEGACY_RENDERER_H__
#define __CRYSTAL_SHADER_LEGACY_RENDERER_H__



namespace Crystal {
	namespace Graphics {
		template<typename>
		class ICamera;
		template<typename>
		class PointLight;
		class PointBuffer;
		class LineBuffer;
		class TriangleBuffer;
	}
	namespace Shader {

class LegacyRenderer
{
public:
	void render(const Graphics::ICamera<float>& camera, const Graphics::PointBuffer& buffer);

	void renderId(const Graphics::ICamera<float>& camera, const Graphics::PointBuffer& buffer);

	void renderAlphaBlend(const Graphics::ICamera<float>& camera, const Graphics::PointBuffer& buffer);

	void render(const Graphics::ICamera<float>& camera, const Graphics::LineBuffer& buffer);

	void render(const Graphics::ICamera<float>& camera, const Graphics::PointLight<float>& light, const Graphics::TriangleBuffer& buffer);

	void renderId(const Graphics::ICamera<float>& camera, const Graphics::TriangleBuffer& buffer);

};

	}
}

#endif