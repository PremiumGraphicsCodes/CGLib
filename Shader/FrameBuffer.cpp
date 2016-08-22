#include "stdafx.h"
#include "FrameBuffer.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

void FrameBuffer::build(int width, int height)
{
	this->width = width;
	this->height = height;
	glGenFramebuffers(1, &frameBuffer);

	assert(GL_NO_ERROR == glGetError());
}

void FrameBuffer::setTexture(const TextureObject& texture)
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture.getTexHandle(), 0);

	//glBindRenderbuffer(GL_RENDERBUFFER, 0);
	//glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void FrameBuffer::bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
	//glBindTexture(GL_TEXTURE_2D, texture.getId());
	assert(GL_NO_ERROR == glGetError());
}

void FrameBuffer::unbind()
{
	//glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	assert(GL_NO_ERROR == glGetError());
}

#include <iostream>

Image FrameBuffer::toImage() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glReadBuffer(GL_COLOR_ATTACHMENT0);
	std::vector<unsigned char> values(width * height * 4);

	glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, values.data());

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return Image(width, height, values);
}

ColorRGBA<unsigned char> FrameBuffer::getColor(const int x, const int y) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glReadBuffer(GL_COLOR_ATTACHMENT0);
	std::vector<unsigned char> values(4);

	glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, values.data());

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return ColorRGBA<unsigned char>(values[0], values[1], values[2], values[3]);
}

ColorRGBA<float> FrameBuffer::getColorf(const int x, const int y) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glReadBuffer(GL_COLOR_ATTACHMENT0);
	std::vector<float> values(4);

	glReadPixels(x, y, 1, 1, GL_RGBA, GL_FLOAT, values.data());

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return ColorRGBA<float>(values[0], values[1], values[2], values[3]);
}

std::vector<ColorRGBA<unsigned char>> FrameBuffer::getColors(const int x, const int y, const int width, const int height) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glReadBuffer(GL_COLOR_ATTACHMENT0);
	std::vector<unsigned char> values(width * height * 4);

	glReadPixels(x, y, width, height, GL_RGBA, GL_UNSIGNED_BYTE, values.data());

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	std::vector<ColorRGBA<unsigned char>> results;
	for (int i = 0; i < values.size(); i += 4) {
		results.push_back(ColorRGBA<unsigned char>(values[i + 0], values[i + 1], values[i + 2], values[i + 3]));
	}

	return results;
}

std::vector<ColorRGBA<float>> FrameBuffer::getColorsf(const int x, const int y, const int width, const int height) const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glReadBuffer(GL_COLOR_ATTACHMENT0);
	std::vector<float> values(width * height * 4);

	glReadPixels(x, y, width, height, GL_RGBA, GL_FLOAT, values.data());

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	std::vector<ColorRGBA<float>> results;
	for (int i = 0; i < values.size(); i += 4) {
		results.push_back(ColorRGBA<float>(values[i + 0], values[i + 1], values[i + 2], values[i + 3]));
	}

	return results;
}
