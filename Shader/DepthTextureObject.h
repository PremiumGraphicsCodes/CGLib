#ifndef __CRYSTAL_SHADER_DEPTH_TEXTURE_OBJECT_H__
#define __CRYSTAL_SHADER_DEPTH_TEXTURE_OBJECT_H__

#include "GLee.h"
#include "../Graphics/Image.h"
#include "ITextureObject.h"

namespace Crystal {
	namespace Shader {

class DepthTextureObject : public ITextureObject
{
public:
	DepthTextureObject(const int id = 0) :
		ITextureObject(id)
	{}

	DepthTextureObject(const Graphics::Imagef& image, const int id = 0);

	void create(const Graphics::Imagef& image, const int id = 0);

	void bind() const override;

	void unbind() const override;

};

	}
}
#endif