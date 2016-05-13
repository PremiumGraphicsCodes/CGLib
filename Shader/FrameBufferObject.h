#ifndef __CRYSTAL_SHADER_FRAME_BUFFER_OBJECT_H__
#define __CRYSTAL_SHADER_FRAME_BUFFER_OBJECT_H__

#include "GLee.h"
#include "../Graphics/Image.h"
#include "TextureObject.h"
#include "DepthTexture.h"
#include <cassert>
#include <vector>

namespace Crystal {
	namespace Shader {

class FrameBufferObject
{
public:
	~FrameBufferObject() {
		unbind();
	}

	bool build(int width, int height);

	void setColorTexture(const TextureObject& texture);

	void setDepthTexture(const DepthTexture& texture);

	void bind();

	void unbind();

	void bindDepth();

	void unbindDepth();

	int getWidth() const { return width; }

	int getHeight() const { return height; }

	TextureObject* getColorTexture() { return &colorTexture; }

private:
	GLuint frameBuffer;
	TextureObject colorTexture;
	DepthTexture depthTexture;
	int width;
	int height;
	//GLuint rboId;

};
	}
}
#endif