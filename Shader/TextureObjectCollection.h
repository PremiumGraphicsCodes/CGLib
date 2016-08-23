#ifndef __CRYSTAL_SHADER_TEXTURE_OBJECT_COLLECTION_H__
#define __CRYSTAL_SHADER_TEXTURE_OBJECT_COLLECTION_H__

#include "ITextureObject.h"
#include <list>
#include "../Util/UnCopyable.h"

namespace Crystal {
	namespace Shader {
		class TextureObject;
		class DepthTextureObject;

class TextureObjectCollection : private UnCopyable
{
public:
	TextureObjectCollection();

	~TextureObjectCollection();

	void clear();

	TextureObject* create(const Graphics::Image& image);

	TextureObject* create(const Graphics::Imagef& image);

	DepthTextureObject* createDepth(const Graphics::Imagef& image);

	std::list<TextureObject*> create(const Graphics::Texture& tex);

private:
	std::list<ITextureObject*> textures;
	int nextId;
};
	}
}

#endif