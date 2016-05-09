#ifndef __CRYSTAL_SHADER_SMOOTH_RENDERER_H__
#define __CRYSTAL_SHADER_SMOOTH_RENDERER_H__

#include <map>
#include <vector>

#include "../Shader/ShaderObject.h"

#include "../Graphics/TriangleBuffer.h"
#include "../Graphics/Light.h"

#include "IRenderer.h"

namespace Crystal {
	namespace Graphics {
		class Material;
	}
	namespace Shader {

class SmoothRenderer
{
public:

	SmoothRenderer() = default;

	~SmoothRenderer() = default;

	void findLocation();

	void render(const Graphics::ICamera<float>& camera, const Graphics::TriangleBuffer& buffer, const Graphics::PointLight<float>& light, const Graphics::Material& material);

	bool build();

private:

	std::string getBuildinVertexShaderSource() const;

	std::string getBuildinFragmentShaderSource() const;

	struct Location {
		GLuint projectionMatrix;
		GLuint modelviewMatrix;
		GLuint position;
		GLuint id;
	};

	Location location;
	ShaderObject shader;

};


	}
}

#endif