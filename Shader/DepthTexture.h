#ifndef __CRYSTAL_SHADER_DEPTH_TEXTURE_H__
#define __CRYSTAL_SHADER_DEPTH_TEXTURE_H__

#include "GLee.h"
#include "../Graphics/Image.h"
#include "ITextureObject.h"

namespace Crystal {
	namespace Shader {

class DepthTexture : public ITextureObject
{
public:
	DepthTexture(const int id = 0) :
		ITextureObject(id)
	{}

	DepthTexture(const Graphics::Imagef& image, const int id = 0);

	bool create(const Graphics::Imagef& image, const int id = 0);

	void bind() const override;

	void unbind() const override;

};

	}
}
#endif