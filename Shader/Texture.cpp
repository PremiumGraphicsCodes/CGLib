#include "Texture.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

Texture::Texture(const Image& image, const int id)
{
	create(image, id);
}

bool Texture::create(const Image& image, const int id)
{
	this->id = id;
	this->width = image.getWidth();
	this->height = image.getHeight();

	glActiveTexture(GL_TEXTURE0 + id);
	glGenTextures(1, &texHandle);
	glBindTexture(GL_TEXTURE_2D, texHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getValues().data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);


	glBindTexture(GL_TEXTURE_2D, 0);
	return (GL_NO_ERROR == glGetError());
}

void Texture::bind() const
{
	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(GL_TEXTURE_2D, texHandle);
}

void Texture::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
}


Texturef::Texturef(const Imagef& image, const int id)
{
	create(image, id);
}

bool Texturef::create(const Imagef& image, const int id)
{
	this->id = id;
	this->width = image.getWidth();
	this->height = image.getHeight();

	glActiveTexture(GL_TEXTURE0 + id);
	glGenTextures(1, &texHandle);
	glBindTexture(GL_TEXTURE_2D, texHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_FLOAT, image.getValues().data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);


	glBindTexture(GL_TEXTURE_2D, 0);
	return (GL_NO_ERROR == glGetError());
}

void Texturef::bind() const
{
	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(GL_TEXTURE_2D, texHandle);
}

void Texturef::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(GL_TEXTURE0);
}
