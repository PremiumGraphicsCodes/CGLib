#ifndef __CRYSTAL_SHADER_TEXTURE_H__
#define __CRYSTAL_SHADER_TEXTURE_H__

#include "GLee.h"
#include "../Graphics/Image.h"
#include "ITexture.h"

namespace Crystal {
	namespace Shader {


class Texture : public ITexture
{
public:
	Texture(const int id = 0) :
		ITexture(id)
	{}

	Texture(const Graphics::Image& image, const int id = 0);

	bool create(const Graphics::Image& image, const int id = 0);

	void bind() const override;

	void unbind() const override;


private:
};

class Texturef : public ITexture
{
public:
	Texturef(const int id = 0) :
		ITexture(id)
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