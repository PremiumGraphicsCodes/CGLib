#include "DepthBuffer.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool DepthBuffer::build(int width, int height, const int textureId)
{
	this->width = width;
	this->height = height;
	glGenFramebuffersEXT(1, &frameBuffer);
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, frameBuffer);

	texture.create(Imagef(width, height), textureId);
	glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_TEXTURE_2D, texture.getTexHandle(), 0);

	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);

	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);

	return (GL_NO_ERROR == glGetError());
}

bool DepthBuffer::bind()
{
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, frameBuffer);
	texture.bind();
	return (GL_NO_ERROR == glGetError());
}

bool DepthBuffer::unbind()
{
	texture.unbind();
	glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0);
	return (GL_NO_ERROR == glGetError());
}

Imagef DepthBuffer::toImage() const
{
	glBindFramebuffer(GL_FRAMEBUFFER_EXT, frameBuffer);
	texture.bind();

	glReadBuffer(GL_DEPTH_ATTACHMENT_EXT);
	std::vector<float> values(width * height * 4);

	glReadPixels(0, 0, width, height, GL_RGBA, GL_FLOAT, values.data());

	texture.unbind();
	glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);

	return Imagef(width, height, values);
}

ColorRGBA<float> DepthBuffer::getColor(const int x, const int y) const
{
	glBindFramebuffer(GL_FRAMEBUFFER_EXT, frameBuffer);
	texture.bind();

	glReadBuffer(GL_DEPTH_ATTACHMENT_EXT);
	std::vector<float> values(4);

	glReadPixels(x, y, 1, 1, GL_RGBA, GL_FLOAT, values.data());

	texture.unbind();
	glBindFramebuffer(GL_FRAMEBUFFER_EXT, 0);

	return ColorRGBA<float>(values[0], values[1], values[2], values[3]);

}
