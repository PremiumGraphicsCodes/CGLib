#ifndef __CRYSTAL_SHADER_SCENE_H__
#define __CRYSTAL_SHADER_SCENE_H__

#include "VisualObject.h"

namespace Crystal {
	namespace Shader {

class Scene
{
public:
	Scene();

	void add(const VisualObject& object) {
		visualObjects.push_back(object);
	}

	void renderLines();

	void renderPoints();

	void renderTriangles();

private:
	std::vector<VisualObject> visualObjects;
};
	}
}

#endif