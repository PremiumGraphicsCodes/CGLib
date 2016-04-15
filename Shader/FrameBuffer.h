#ifndef __CRYSTAL_SHADER_FRAME_BUFFER_H__
#define __CRYSTAL_SHADER_FRAME_BUFFER_H__

#include "GLee.h"
#include "../Graphics/Image.h"
#include "Texture.h"
#include <cassert>
#include <vector>

namespace Crystal {
	namespace Shader {

class FrameBuffer
{
public:
	~FrameBuffer() {
		unbind();
	}

	bool build(int width, int height, const int textureId = 0);

	bool bind();

	bool unbind();

	Graphics::Image toImage() const;

	Graphics::ColorRGBA<unsigned char> getColor(const int x, const int y) const;

	int getWidth() const { return width; }

	int getHeight() const { return height; }

	Texture<unsigned char>* getTexture() { return &texture; }

private:
	GLuint frameBuffer;
	Texture<unsigned char> texture;
	int width;
	int height;
};

class FrameBufferf
{
public:
	~FrameBufferf() {
		unbind();
	}

	bool build(int width, int height, const int textureId = 0);

	bool bind();

	bool unbind();

	Graphics::Imagef toImage() const;

	Graphics::ColorRGBA<float> getColor(const int x, const int y) const;

	int getWidth() const { return width; }

	int getHeight() const { return height; }

	Texturef* getTexture() { return &texture; }

private:
	GLuint frameBuffer;
	Texturef texture;
	int width;
	int height;
};

	}
}

#endif
