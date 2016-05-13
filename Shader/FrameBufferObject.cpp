#include "FrameBufferObject.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool FrameBufferObject::build(int width, int height)
{
	this->width = width;
	this->height = height;
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return (GL_NO_ERROR == glGetError());
}

void FrameBufferObject::setColorTexture(const TextureObject& texture)
{
	this->colorTexture = texture;
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getTexHandle(), 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferObject::setDepthTexture(const DepthTexture& texture)
{
	this->depthTexture = texture;
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture.getTexHandle(), 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}


void FrameBufferObject::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	colorTexture.bind();
}

void FrameBufferObject::unbind()
{
	colorTexture.unbind();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void FrameBufferObject::bindDepth()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	depthTexture.bind();
}

void FrameBufferObject::unbindDepth()
{
	depthTexture.unbind();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

