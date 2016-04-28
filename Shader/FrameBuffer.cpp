#include "FrameBuffer.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

bool FrameBuffer::build(int width, int height)
{
	this->width = width;
	this->height = height;
	glGenFramebuffers(1, &frameBuffer);

	return (GL_NO_ERROR == glGetError());
}

void FrameBuffer::setTexture(const Texture& texture)
{
	this->texture = texture;
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getTexHandle(), 0);

	//glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}


bool FrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	texture.bind();
	//glBindTexture(GL_TEXTURE_2D, texture.getId());
	return (GL_NO_ERROR == glGetError());
}

bool FrameBuffer::unbind(){
	texture.unbind();
	//glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return (GL_NO_ERROR == glGetError());
}

#include <iostream>

Image FrameBuffer::toImage() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	texture.bind();

	glReadBuffer(GL_COLOR_ATTACHMENT0);
	std::vector<unsigned char> values(width * height * 4);

	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, values.data());

	texture.unbind();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return Image(width, height, values);
}

ColorRGBA<unsigned char> FrameBuffer::getColor(const int x, const int y) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	texture.bind();

	glReadBuffer(GL_COLOR_ATTACHMENT0);
	std::vector<unsigned char> values(4);

	glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, values.data());

	texture.unbind();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return ColorRGBA<unsigned char>(values[0], values[1], values[2], values[3]);

}


bool FrameBufferf::build(int width, int height, const int textureId)
{
	this->width = width;
	this->height = height;
	glGenFramebuffers(1, &frameBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	//glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return (GL_NO_ERROR == glGetError());
}

void FrameBufferf::setTexture(const Texturef& texture)
{
	this->texture = texture;
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getTexHandle(), 0);

	//glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}


bool FrameBufferf::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	texture.bind();
	//glBindTexture(GL_TEXTURE_2D, texture.getId());
	return (GL_NO_ERROR == glGetError());
}

bool FrameBufferf::unbind() {
	texture.unbind();
	//glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return (GL_NO_ERROR == glGetError());
}

Imagef FrameBufferf::toImage() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	texture.bind();

	glReadBuffer(GL_COLOR_ATTACHMENT0);
	std::vector<float> values(width * height * 4);

	glReadPixels(0, 0, width, height, GL_RGBA, GL_FLOAT, values.data());

	texture.unbind();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return Imagef(width, height, values);
}

ColorRGBA<float> FrameBufferf::getColor(const int x, const int y) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	texture.bind();

	glReadBuffer(GL_COLOR_ATTACHMENT0);
	std::vector<float> values(4);

	glReadPixels(x, y, 1, 1, GL_RGBA, GL_FLOAT, values.data());

	texture.unbind();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return ColorRGBA<float>(values[0], values[1], values[2], values[3]);

}




