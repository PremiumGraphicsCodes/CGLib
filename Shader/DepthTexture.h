#ifndef __CRYSTAL_SHADER_DEPTH_TEXTURE_H__
#define __CRYSTAL_SHADER_DEPTH_TEXTURE_H__

#include "GLee.h"
#include "../Graphics/Image.h"

namespace Crystal {
	namespace Shader {

class DepthTexture
{
public:
	DepthTexture(const int id = 0) :
		id(id)
	{}

	DepthTexture(const Graphics::Imagef& image, const int id = 0);

	bool create(const Graphics::Imagef& image, const int id = 0);

	~DepthTexture() { unbind(); }

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