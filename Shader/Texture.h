#ifndef __CRYSTAL_SHADER_TEXTURE_H__
#define __CRYSTAL_SHADER_TEXTURE_H__

#include "GLee.h"
#include "../Graphics/Image.h"

namespace Crystal {
	namespace Shader {

template<typename ColorType>
class Texture
{
public:
	Texture() = default;

	Texture(const Graphics::Image<ColorType>& image);

	bool create(const Graphics::Image<ColorType>& image);

	~Texture() { unbind(); }

	void bind() const;

	void unbind() const;

	GLuint getId() const { return texHandle; }

private:
	GLuint texHandle;

};
	}
}

#endif