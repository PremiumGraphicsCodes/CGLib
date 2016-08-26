#ifndef __CRYSTAL_SHADER_NORMAL_RENDERER_H__
#define __CRYSTAL_SHADER_NORMAL_RENDERER_H__

#include "../Graphics/ICamera.h"
#include "../Graphics/PointBuffer.h"
#include "IRenderer.h"

namespace Crystal {
	namespace Shader {

class NormalBuffer
{
public:
	NormalBuffer() {};

	void add(const Math::Vector3d<float>& position, const Math::Vector3d<float>& normal, const Graphics::ColorRGBA<float>& color);

	Graphics::Buffer3d<float> getPosition() const { return position; }

	Graphics::Buffer3d<float> getNormal() const { return normal; }

	Graphics::Buffer4d<float> getColor() const { return color; }

private:
	Graphics::Buffer3d<float> position;
	Graphics::Buffer3d<float> normal;
	Graphics::Buffer4d<float> color;
};

namespace v330 {

class NormalRenderer
{
public:
	void findLocation();

	void render(const Graphics::ICamera<float>& camera, const NormalBuffer& buffer);

	bool build();

private:

	std::string getBuildinVertexShaderSource() const;

	std::string getBuildinGeometryShaderSource() const;

	std::string getBuildinFragmentShaderSource() const;

private:
	ShaderObject shader;
};
		}
	}
}

#endif