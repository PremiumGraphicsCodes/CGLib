#ifndef __CRYSTAL_SHADER_TEXTURE_HANDLER_H__
#define __CRYSTAL_SHADER_TEXTURE_HANDLER_H__

#include "../Util/UnCopyable.h"
#include "TextureObject.h"
#include <map>

namespace Crystal {
	namespace Shader {

class TextureHandler : private UnCopyable
{
public:
	static TextureHandler* getInstance() {
		static TextureHandler instance;
		return &instance;
	}

	~TextureHandler() {
		clear();
	}

	void clear() {
		for (auto t : textures) {
			delete t.second;
		}
		textures.clear();
	}

	bool has(const std::string& name) {
		return textures.find(name) != textures.end();
	}

	TextureObject* get(const std::string& name) { return textures[name]; }

private:
	TextureHandler() = default;

	std::map<std::string, TextureObject* > textures;
};
	}
}

#endif