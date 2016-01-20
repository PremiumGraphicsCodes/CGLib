#ifndef __CRYSTAL_SHADER_LEGACY_SELECTION_RENDERER_H__
#define __CRYSTAL_SHADER_LEGACY_SELECTION_RENDERER_H__

namespace Crystal {
	namespace Shader {

class LegacySelectionRenderer
{
public:
	void render();

	void pick(int x, int y);
};
	}
}

#endif