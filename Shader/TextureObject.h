#ifndef __CRYSTAL_SHADER_TEXTURE_H__
#define __CRYSTAL_SHADER_TEXTURE_H__

#include "GLee.h"
#include "../Graphics/Image.h"
#include "ITextureObject.h"

namespace Crystal {
	namespace Shader {


class TextureObject : public ITextureObject
{
public:
	TextureObject(const int id = 0) :
		ITextureObject(id)
	{}

	TextureObject(const Graphics::Image& image, const int id = 0);

	TextureObject(const Graphics::Imagef& image, const int id = 0);

	bool create(const Graphics::Image& image, const int id = 0);

	bool create(const Graphics::Imagef& image, const int id = 0);

	void bind() const override;

	void unbind() const override;


private:
};


	}
}

#endif