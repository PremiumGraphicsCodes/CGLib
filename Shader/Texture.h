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
	Texture(const int id = 0) :
		id(id)
	{}

	Texture(const Graphics::Image<ColorType>& image, const int id = 0);

	bool create(const Graphics::Image<ColorType>& image, const int id = 0);

	~Texture() { unbind(); }

	void bind() const;

	void unbind() const;

	int getId() const { return id; }

	GLuint getTexHandle() const { return texHandle; }

	int getWidth() const { return width; }

	int getHeight() const { return height; }

private:
	int id;
	GLuint texHandle;
	int width;
	int height;
};
	}
}

#endif