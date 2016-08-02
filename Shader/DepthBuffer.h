#ifndef __CRYSTAL_SHADER_DEPTH_BUFFER_H__
#define __CRYSTAL_SHADER_DEPTH_BUFFER_H__

#include "DepthTextureObject.h"
#include "../Graphics/Image.h"

namespace Crystal {
	namespace Shader {

class DepthBuffer
{
public:
	~DepthBuffer() {
		unbind();
	}

	void setTexture(const DepthTextureObject& texture);

	bool build(const DepthTextureObject& depthTexture);

	bool bind() const;

	bool unbind() const;

	int getWidth() const { return width; }

	int getHeight() const { return height; }

	DepthTextureObject* getTexture() { return &texture; }

private:
	GLuint frameBuffer;
	DepthTextureObject texture;
	int width;
	int height;
};

	}
}

#endif