#ifndef __CRYSTAL_SHADER_IMAGE_TEXTURE_MAP_H__
#define __CRYSTAL_SHADER_IMAGE_TEXTURE_MAP_H__

#include <map>

namespace Crystal {
	namespace Graphics {
		class Image;
	}
	namespace Shader {
		class TextureObject;
		using ImageTextureMap = std::map<Graphics::IImage*, TextureObject*>;
	}
}

#endif
