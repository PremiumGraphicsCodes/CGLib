#ifndef __CRYSTAL_SHADER_TEXTURE_OBJECT_REPOSITORY_H__
#define __CRYSTAL_SHADER_TEXTURE_OBJECT_REPOSITORY_H__

#include "ITextureObject.h"
#include <list>
#include "../Util/UnCopyable.h"
#include "ImageTextureMap.h"

namespace Crystal {
	namespace Shader {
		class TextureObject;
		class DepthTextureObject;

class TextureObjectRepository : private UnCopyable
{
public:
	TextureObjectRepository();

	~TextureObjectRepository();

	void clear();

	TextureObject* create(const Graphics::Image& image);

	TextureObject* create(const Graphics::Imagef& image);

	TextureObject* create(Graphics::Image* image);

	TextureObject* create(Graphics::Imagef* image);

	DepthTextureObject* createDepth(const Graphics::Imagef& image);

	bool has(Graphics::IImage* image);

	TextureObject* find(Graphics::IImage* image);

	void update(Graphics::Image* image);

	void update(Graphics::Imagef* image);

private:
	std::list<ITextureObject*> textures;
	ImageTextureMap imageTexMap;
	int nextId;
};

	}
}

#endif