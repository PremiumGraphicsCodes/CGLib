#ifndef __CRYSTAL_SHADER_PARTICLE_DEPTH_RENDERER_H__
#define __CRYSTAL_SHADER_PARTICLE_DEPTH_RENDERER_H__

#include "../Graphics/ICamera.h"
#include "../Graphics/PointBuffer.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

class ParticleDepthRenderer
{
public:
	void render(const Graphics::ICamera<float>& camera, const Graphics::PointBuffer& buffer);

	bool build();

private:
	std::string getBuildinVertexShaderSource() const;
	
	std::string getBuildinFragmentShaderSource() const;

	void findLocation();


private:
	ShaderObject shader;
};

	}
}

#endif