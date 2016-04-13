#ifndef __CRYSTAL_SHADER_CUBE_MAP_TEXTURE_H__
#define __CRYSTAL_SHADER_CUBE_MAP_TEXTURE_H__

#include "../Graphics/Image.h"

namespace Crystal {
	namespace Shader {

class CubeMapTexture
{
public:
	void create(const Crystal::Graphics::Image<float>& image, const unsigned int id);

	void bind() const;

	void unbind() const;
private:
	unsigned int texHandle;
	unsigned int id;
};

	}
}

#endif