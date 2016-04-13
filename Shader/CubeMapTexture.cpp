#include "GLee.h"
#include "CubeMapTexture.h"

using namespace Crystal::Shader;

void CubeMapTexture::create(const Crystal::Graphics::Image<float>& image, const unsigned int id)
{
	this->id = id;
	glActiveTexture(GL_TEXTURE0 + id);
	glGenTextures(1, &texHandle);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texHandle);

	std::vector<float> tests(image.getWidth() * image.getHeight() * 4, 0.0f);
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_FLOAT, image.getValues().data());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_FLOAT, image.getValues().data());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_FLOAT, image.getValues().data());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_FLOAT, image.getValues().data());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_FLOAT, image.getValues().data());
	glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, image.getWidth(), image.getHeight(), 0, GL_RGBA, GL_FLOAT, image.getValues().data());

	//glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	//glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);
	//glTexGeni(GL_R, GL_TEXTURE_GEN_MODE, GL_REFLECTION_MAP);

	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void CubeMapTexture::bind() const
{
	glEnable(GL_TEXTURE_CUBE_MAP);
	glActiveTexture(GL_TEXTURE0 + id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texHandle);
}

void CubeMapTexture::unbind() const
{
	glDisable(GL_TEXTURE_CUBE_MAP);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
