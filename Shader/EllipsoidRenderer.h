#ifndef __CRYSTAL_SHADER_ELLIPSOID_RENDERER_H__
#define __CRYSTAL_SHADER_ELLIPSOID_RENDERER_H__

#include "../Graphics/ICamera.h"
#include "../Graphics/EllipsoidBuffer.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

class EllipsoidRenderer
{
public:
	void findLocation();

	void render(const Graphics::ICamera<float>& camera, const Graphics::EllipsoidBuffer& buffer);

	//void changeSize(const float size) { this->pointSize = size; }
	bool build();

private:

	std::string getBuildinVertexShaderSource() const;

	std::string getBuildinFragmentShaderSource() const;

private:
	ShaderObject shader;
};

	}
}

#endif