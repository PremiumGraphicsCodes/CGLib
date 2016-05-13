#ifndef __CRYSTAL_SHADER_TEXTURE_H__
#define __CRYSTAL_SHADER_TEXTURE_H__

#include "GLee.h"
#include "../Graphics/Image.h"
#include "ITextureObject.h"

namespace Crystal {
	namespace Shader {


class Texture : public ITextureObject
{
public:
	Texture(const int id = 0) :
		ITextureObject(id)
	{}

	Texture(const Graphics::Image& image, const int id = 0);

	bool create(const Graphics::Image& image, const int id = 0);

	void bind() const override;

	void unbind() const override;


private:
};

class Texturef : public ITextureObject
{
public:
	Texturef(const int id = 0) :
		ITextureObject(id)
	{}

	Texturef(const Graphics::Imagef& image, const int id = 0);

	bool create(const Graphics::Imagef& image, const int id = 0);

	void bind() const override;

	void unbind() const override;

private:
};


	}
}

#endif