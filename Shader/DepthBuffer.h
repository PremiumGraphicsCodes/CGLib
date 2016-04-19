#ifndef __CRYSTAL_SHADER_DEPTH_BUFFER_H__
#define __CRYSTAL_SHADER_DEPTH_BUFFER_H__

#include "DepthTexture.h"
#include "../Graphics/Image.h"

namespace Crystal {
	namespace Shader {

class DepthBuffer
{
public:
	~DepthBuffer() {
		unbind();
	}

	bool build(int width, int height, const int textureId = 0);

	bool bind();

	bool unbind();

	Graphics::Imagef toImage() const;

	Graphics::ColorRGBA<float> getColor(const int x, const int y) const;

	int getWidth() const { return width; }

	int getHeight() const { return height; }

	DepthTexture* getTexture() { return &texture; }

private:
	GLuint frameBuffer;
	DepthTexture texture;
	int width;
	int height;
};

	}
}

#endif