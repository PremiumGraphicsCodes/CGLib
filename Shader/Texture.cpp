#include "Texture.h"

using namespace Crystal::Graphics;
using namespace Crystal::Shader;

template<typename ColorType>
Texture<ColorType>::Texture(const Image<ColorType>& image)
{
	create(image);
}

template<typename ColorType>
bool Texture<ColorType>::create(const Image<ColorType>& image)
{
	//glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &texHandle);
	glBindTexture(GL_TEXTURE_2D, texHandle);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getValues().data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);


	glBindTexture(GL_TEXTURE_2D, 0);
	return (GL_NO_ERROR == glGetError());
}

template<typename ColorType>
void Texture<ColorType>::bind() const
{
	glBindTexture(GL_TEXTURE_2D, texHandle);
}

template<typename ColorType>
void Texture<ColorType>::unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}


template class Texture<unsigned char>;
